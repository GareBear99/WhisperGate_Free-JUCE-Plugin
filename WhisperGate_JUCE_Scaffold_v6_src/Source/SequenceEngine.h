#pragma once
#include <juce_core/juce_core.h>
#include <vector>
class SequenceEngine
{
public:
    struct Step { juce::String name="Step"; float energy=0.5f; juce::uint32 colour=0xffaa3344; };
    void addStep (const Step& step);
    void removeStep (int index);
    void clear();
    void setPlaying (bool shouldPlay);
    bool isPlaying() const noexcept { return playing; }
    const std::vector<Step>& getSteps() const noexcept { return steps; }
    int getPlayIndex() const noexcept { return playIndex; }
    void tick();
private:
    std::vector<Step> steps;
    bool playing=false;
    int playIndex=-1;
};
