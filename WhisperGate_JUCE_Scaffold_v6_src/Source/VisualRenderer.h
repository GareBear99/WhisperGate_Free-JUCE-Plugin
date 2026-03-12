#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "RuneManager.h"
#include "RuneComboEngine.h"
#include "SequenceEngine.h"
class VisualRenderer
{
public:
    void setRitualCharge (float newCharge) noexcept { ritualCharge = juce::jlimit(0.0f,1.0f,newCharge); }
    void setRingValues (std::array<float, 7> values) { rings = values; }
    void paint (juce::Graphics& g, juce::Rectangle<int> bounds,const RuneManager& runeManager,const RuneComboEngine::ComboFlags& combos,const SequenceEngine& sequence);
private:
    void paintBackground (juce::Graphics& g, juce::Rectangle<int> b);
    void paintRings (juce::Graphics& g, juce::Point<float> c, float radiusBase);
    void paintRunes (juce::Graphics& g, juce::Point<float> c, float radius, const RuneManager& runeManager);
    void paintCore (juce::Graphics& g, juce::Point<float> c, float radius);
    void paintParticles (juce::Graphics& g, juce::Point<float> c, float radius);
    void paintMemoryArc (juce::Graphics& g, juce::Point<float> c, float radius, const SequenceEngine& sequence);
    float ritualCharge=0.0f;
    std::array<float,7> rings{0.5f,0.45f,0.35f,0.55f,0.30f,0.60f,0.40f};
};
