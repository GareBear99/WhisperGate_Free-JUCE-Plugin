#pragma once
#include <juce_core/juce_core.h>
class UISfxEngine
{
public:
    void triggerHover(){ lastTrigger = "hover"; }
    void triggerActivate(){ lastTrigger = "activate"; }
    void triggerSave(){ lastTrigger = "save"; }
    void setLevel (float newLevel) noexcept { level = newLevel; }
    juce::String getLastTrigger() const noexcept { return lastTrigger; }
private:
    float level=0.25f;
    juce::String lastTrigger="none";
};
