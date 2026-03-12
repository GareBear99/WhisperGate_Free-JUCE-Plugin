#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <array>

enum class RuneId { seed=0, whisper, breath, drift, autoMode, choir, temple, echo, presence, count };
struct RuneState { bool active=false; bool hovered=false; bool armed=false; bool comboLinked=false; };

class RuneManager
{
public:
    RuneManager();
    RuneState& getState (RuneId id);
    const RuneState& getState (RuneId id) const;
    void clearHover();
    void clearComboFlags();
    void toggle (RuneId id);
    void setActive (RuneId id, bool shouldBeActive);
    bool isActive (RuneId id) const;
    int getActiveCount() const;
    static juce::String toString (RuneId id);
private:
    std::array<RuneState, static_cast<size_t>(RuneId::count)> states;
};
