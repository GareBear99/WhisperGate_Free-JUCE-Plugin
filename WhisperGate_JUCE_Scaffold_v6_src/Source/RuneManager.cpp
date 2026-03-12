#include "RuneManager.h"
RuneManager::RuneManager() = default;
RuneState& RuneManager::getState (RuneId id) { return states[static_cast<size_t>(id)]; }
const RuneState& RuneManager::getState (RuneId id) const { return states[static_cast<size_t>(id)]; }
void RuneManager::clearHover() { for (auto& s : states) s.hovered = false; }
void RuneManager::clearComboFlags() { for (auto& s : states) s.comboLinked = false; }
void RuneManager::toggle (RuneId id) { auto& s = getState(id); s.active = !s.active; }
void RuneManager::setActive (RuneId id, bool shouldBeActive) { getState(id).active = shouldBeActive; }
bool RuneManager::isActive (RuneId id) const { return getState(id).active; }
int RuneManager::getActiveCount() const { int total = 0; for (const auto& s : states) total += s.active ? 1 : 0; return total; }
juce::String RuneManager::toString (RuneId id)
{
    switch (id)
    {
        case RuneId::seed: return "Seed";
        case RuneId::whisper: return "Whisper";
        case RuneId::breath: return "Breath";
        case RuneId::drift: return "Drift";
        case RuneId::autoMode: return "Auto";
        case RuneId::choir: return "Choir";
        case RuneId::temple: return "Temple";
        case RuneId::echo: return "Echo";
        case RuneId::presence: return "Presence";
        default: return "Unknown";
    }
}
