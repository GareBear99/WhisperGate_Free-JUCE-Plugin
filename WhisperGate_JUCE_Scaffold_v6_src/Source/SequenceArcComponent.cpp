#include "SequenceArcComponent.h"
void SequenceArcComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
    auto area=getLocalBounds().reduced(4);
    g.setColour(juce::Colours::darkred.withAlpha(0.35f)); g.drawRoundedRectangle(area.toFloat(),10.0f,2.0f);
    const auto& steps=sequence.getSteps(); if(steps.empty()) return;
    int w=juce::jmax(20, area.getWidth()/(int)steps.size());
    for(size_t i=0;i<steps.size();++i)
    {
        auto r=juce::Rectangle<int>(area.getX()+(int)i*w, area.getY(), w-4, area.getHeight());
        auto c=juce::Colour(steps[i].colour); if((int)i==sequence.getPlayIndex()) c=c.brighter(0.30f);
        g.setColour(c.withAlpha(0.9f)); g.fillRoundedRectangle(r.toFloat().reduced(3.0f),8.0f);
    }
}
