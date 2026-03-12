#pragma once
#include <juce_events/juce_events.h>
class UIEventRouter
{
public:
    struct Event { juce::String type; juce::String detail; };
    void push (Event e) { lastEvent = std::move(e); }
    const Event& getLastEvent() const noexcept { return lastEvent; }
private:
    Event lastEvent;
};
