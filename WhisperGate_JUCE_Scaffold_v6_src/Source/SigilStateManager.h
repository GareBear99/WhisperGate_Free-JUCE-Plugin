#pragma once
#include <juce_data_structures/juce_data_structures.h>
class SigilStateManager
{
public:
    juce::ValueTree createEmptyState() const;
    juce::String toJson (const juce::ValueTree& state) const;
    juce::ValueTree fromJson (const juce::String& json) const;
};
