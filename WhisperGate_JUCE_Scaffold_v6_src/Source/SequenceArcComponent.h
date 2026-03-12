#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "SequenceEngine.h"
class SequenceArcComponent : public juce::Component
{
public:
    explicit SequenceArcComponent (SequenceEngine& seqRef) : sequence(seqRef) {}
    void paint (juce::Graphics& g) override;
private:
    SequenceEngine& sequence;
};
