#include "CodexDrawerComponent.h"
void CodexDrawerComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black.withAlpha(0.65f));
    g.setColour(juce::Colours::white.withAlpha(0.9f)); g.setFont(16.0f);
    g.drawText("Codex", getLocalBounds().removeFromTop(28), juce::Justification::centredLeft);
    auto area=getLocalBounds().reduced(8).withTrimmedTop(34);
    const auto& entries=manager.getEntries();
    for(const auto& e: entries)
    {
        auto row=area.removeFromTop(36);
        g.setColour(juce::Colour::fromRGB(45,10,12)); g.fillRoundedRectangle(row.toFloat(),8.0f);
        g.setColour(juce::Colours::white.withAlpha(0.85f)); g.drawText(e.title + "  [" + e.tag + "]", row.reduced(8), juce::Justification::centredLeft);
        area.removeFromTop(4);
    }
}
