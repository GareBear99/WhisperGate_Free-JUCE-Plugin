#include "VisualRenderer.h"
void VisualRenderer::paint (juce::Graphics& g, juce::Rectangle<int> bounds,const RuneManager& runeManager,const RuneComboEngine::ComboFlags&,const SequenceEngine& sequence)
{
    paintBackground(g,bounds);
    auto c = bounds.toFloat().getCentre();
    const float base = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.12f;
    paintParticles(g,c,base*4.7f); paintRings(g,c,base); paintRunes(g,c,base*4.9f,runeManager); paintMemoryArc(g,c,base*5.3f,sequence); paintCore(g,c,base);
}
void VisualRenderer::paintBackground (juce::Graphics& g, juce::Rectangle<int> b)
{
    juce::ColourGradient grad(juce::Colour::fromRGB(22,6,8), b.getCentreX(), b.getCentreY(), juce::Colours::black, (float)b.getRight(), (float)b.getBottom(), true);
    g.setGradientFill(grad); g.fillAll();
}
void VisualRenderer::paintRings (juce::Graphics& g, juce::Point<float> c, float radiusBase)
{
    for(size_t i=0;i<rings.size();++i){ float r=radiusBase+(float)i*(radiusBase*0.45f), alpha=0.16f+rings[i]*0.55f, thickness=2.0f+rings[i]*6.0f;
        g.setColour(juce::Colour::fromFloatRGBA(1.0f,0.22f+0.06f*(float)i,0.25f,alpha)); g.drawEllipse(c.x-r,c.y-r,r*2.0f,r*2.0f,thickness); }
}
void VisualRenderer::paintRunes (juce::Graphics& g, juce::Point<float> c, float radius, const RuneManager& rm)
{
    const int count=(int)RuneId::count;
    for(int i=0;i<count;++i){ float a=juce::MathConstants<float>::twoPi*(float)i/(float)count-juce::MathConstants<float>::halfPi;
        float x=c.x+std::cos(a)*radius, y=c.y+std::sin(a)*radius;
        auto state=rm.getState((RuneId)i);
        auto colour=juce::Colour::fromRGB(85,22,26); if(state.active) colour=juce::Colour::fromRGB(210,70,80); if(state.comboLinked) colour=juce::Colour::fromRGB(255,180,120); if(state.hovered) colour=colour.brighter(0.25f);
        g.setColour(colour.withAlpha(0.95f)); g.fillEllipse(x-14.0f,y-14.0f,28.0f,28.0f);
        g.setColour(juce::Colours::white.withAlpha(0.85f)); g.setFont(12.0f);
        g.drawFittedText(RuneManager::toString((RuneId)i).substring(0,1), juce::Rectangle<int>((int)x-10,(int)y-9,20,18), juce::Justification::centred,1);
    }
}
void VisualRenderer::paintCore (juce::Graphics& g, juce::Point<float> c, float radius)
{
    float outer=radius*1.1f+ritualCharge*12.0f, inner=radius*0.48f;
    g.setColour(juce::Colour::fromFloatRGBA(1.0f,0.30f,0.30f,0.78f)); g.fillEllipse(c.x-outer,c.y-outer,outer*2.0f,outer*2.0f);
    g.setColour(juce::Colours::black.withAlpha(0.95f)); g.fillEllipse(c.x-inner,c.y-inner,inner*2.0f,inner*2.0f);
    g.setColour(juce::Colours::white.withAlpha(0.92f)); g.fillEllipse(c.x-12.0f,c.y-12.0f,24.0f,24.0f);
}
void VisualRenderer::paintParticles (juce::Graphics& g, juce::Point<float> c, float radius)
{
    int count=4+(int)std::round(ritualCharge*18.0f);
    for(int i=0;i<count;++i){ float t=(float)i/(float)juce::jmax(1,count-1), a=t*juce::MathConstants<float>::twoPi+ritualCharge*3.0f, wobble=std::sin(a*2.4f+ritualCharge*5.0f)*(14.0f+ritualCharge*25.0f), r=radius+wobble;
        float x=c.x+std::cos(a)*r, y=c.y+std::sin(a)*(r*0.8f); g.setColour(juce::Colour::fromFloatRGBA(1.0f,0.42f,0.22f,0.10f+ritualCharge*0.45f)); g.fillEllipse(x-4.0f,y-4.0f,8.0f,8.0f); }
}
void VisualRenderer::paintMemoryArc (juce::Graphics& g, juce::Point<float> c, float radius, const SequenceEngine& sequence)
{
    auto path=juce::Path(); path.addCentredArc(c.x,c.y,radius,radius,0.0f,juce::degreesToRadians(210.0f),juce::degreesToRadians(330.0f),true);
    g.setColour(juce::Colours::darkred.withAlpha(0.35f)); g.strokePath(path,juce::PathStrokeType(7.0f));
    const auto& steps=sequence.getSteps(); int n=(int)steps.size();
    for(int i=0;i<n;++i){ float t=n==1?0.5f:(float)i/(float)(n-1), ang=juce::degreesToRadians(210.0f+120.0f*t), x=c.x+std::cos(ang)*radius, y=c.y+std::sin(ang)*radius;
        auto col=juce::Colour(steps[(size_t)i].colour); if(i==sequence.getPlayIndex()) col=col.brighter(0.35f);
        g.setColour(col.withAlpha(0.9f)); g.fillEllipse(x-8.0f,y-8.0f,16.0f,16.0f); }
}
