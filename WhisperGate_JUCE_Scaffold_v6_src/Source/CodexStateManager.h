#pragma once
#include <juce_core/juce_core.h>
#include <vector>
class CodexStateManager
{
public:
    struct Entry { juce::String title; juce::String tag; float brightness=0.5f; };
    void addEntry (Entry e);
    const std::vector<Entry>& getEntries() const noexcept { return entries; }
private:
    std::vector<Entry> entries;
};
