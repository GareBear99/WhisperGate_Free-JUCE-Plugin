#include "PluginEditor.h"
#include "ParameterIDs.h"
WhisperGateLiteAudioProcessorEditor::WhisperGateLiteAudioProcessorEditor (WhisperGateLiteAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p), codexDrawer(p.codexStateManager), sequenceArc(p.sequenceEngine)
{
    setSize(980,760);
    codexButton.onClick=[this]{ codexVisible=!codexVisible; codexDrawer.setVisible(codexVisible); };
    addAndMakeVisible(codexButton); addAndMakeVisible(sequenceArc); addAndMakeVisible(codexDrawer); codexDrawer.setVisible(false);
    startTimerHz(30);
}
void WhisperGateLiteAudioProcessorEditor::paint (juce::Graphics& g){ renderer.paint(g, getLocalBounds(), processor.runeManager, processor.getComboFlags(), processor.sequenceEngine); }
void WhisperGateLiteAudioProcessorEditor::resized()
{
    codexButton.setBounds(getWidth()-100,12,84,28); sequenceArc.setBounds(140,getHeight()-110,getWidth()-280,54); codexDrawer.setBounds(getWidth()-260,52,240,getHeight()-64);
}
void WhisperGateLiteAudioProcessorEditor::timerCallback()
{
    renderer.setRitualCharge(processor.computeRitualCharge()); refreshRingValues();
    if(processor.runeManager.isActive(RuneId::autoMode)) processor.sequenceEngine.tick();
    repaint();
}
void WhisperGateLiteAudioProcessorEditor::refreshRingValues()
{
    auto get=[this](const char* id){ return processor.apvts.getRawParameterValue(id)->load(); };
    ringValues = { get(ParamIDs::presence), get(ParamIDs::drift), get(ParamIDs::breath), get(ParamIDs::whisper), get(ParamIDs::echo), get(ParamIDs::temple), get(ParamIDs::width) };
    renderer.setRingValues(ringValues);
}
RuneId WhisperGateLiteAudioProcessorEditor::hitTestRune (juce::Point<float> p) const
{
    auto c = getLocalBounds().toFloat().getCentre(); float radius = juce::jmin((float)getWidth(), (float)getHeight()) * 0.12f * 4.9f; int count=(int)RuneId::count;
    for(int i=0;i<count;++i){ float a=juce::MathConstants<float>::twoPi*(float)i/(float)count-juce::MathConstants<float>::halfPi;
        juce::Point<float> pos(c.x+std::cos(a)*radius, c.y+std::sin(a)*radius); if(pos.getDistanceFrom(p)<20.0f) return (RuneId)i; }
    return RuneId::count;
}
int WhisperGateLiteAudioProcessorEditor::hitTestRing (juce::Point<float> p) const
{
    auto c=getLocalBounds().toFloat().getCentre(); float d=c.getDistanceFrom(p), base=juce::jmin((float)getWidth(), (float)getHeight()) * 0.12f;
    for(int i=0;i<7;++i){ float r=base + (float)i * (base * 0.45f); if(std::abs(d-r)<12.0f) return i; } return -1;
}
void WhisperGateLiteAudioProcessorEditor::mouseMove (const juce::MouseEvent& e)
{
    processor.runeManager.clearHover();
    if(auto r=hitTestRune(e.position); r != RuneId::count){ processor.runeManager.getState(r).hovered=true; processor.uiSfxEngine.triggerHover(); eventRouter.push({"hover", RuneManager::toString(r)}); }
}
void WhisperGateLiteAudioProcessorEditor::mouseDown (const juce::MouseEvent& e)
{
    if(auto r=hitTestRune(e.position); r != RuneId::count){ processor.runeManager.toggle(r); processor.uiSfxEngine.triggerActivate(); eventRouter.push({"toggle", RuneManager::toString(r)}); repaint(); return; }
    draggedRing = hitTestRing(e.position);
}
void WhisperGateLiteAudioProcessorEditor::mouseDrag (const juce::MouseEvent& e)
{
    if(draggedRing < 0) return;
    auto c=getLocalBounds().toFloat().getCentre(); auto distance=c.getDistanceFrom(e.position);
    auto norm=juce::jlimit(0.0f,1.0f,distance/(juce::jmin((float)getWidth(), (float)getHeight()) * 0.6f));
    static const char* paramMap[7] = { ParamIDs::presence, ParamIDs::drift, ParamIDs::breath, ParamIDs::whisper, ParamIDs::echo, ParamIDs::temple, ParamIDs::width };
    if(auto* p=processor.apvts.getParameter(paramMap[draggedRing]))
    {
        p->beginChangeGesture();
        p->setValueNotifyingHost(norm);
    }
}

void WhisperGateLiteAudioProcessorEditor::mouseUp (const juce::MouseEvent&)
{
    if (draggedRing >= 0)
    {
        static const char* paramMap[7] = { ParamIDs::presence, ParamIDs::drift, ParamIDs::breath, ParamIDs::whisper, ParamIDs::echo, ParamIDs::temple, ParamIDs::width };
        if (auto* p = processor.apvts.getParameter(paramMap[draggedRing]))
            p->endChangeGesture();
    }
    draggedRing = -1;
}
