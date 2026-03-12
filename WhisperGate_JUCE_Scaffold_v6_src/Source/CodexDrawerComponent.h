#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "CodexStateManager.h"
class CodexDrawerComponent : public juce::Component
{
public:
    explicit CodexDrawerComponent (CodexStateManager& managerRef) : manager(managerRef) {}
    void paint (juce::Graphics& g) override;
private:
    CodexStateManager& manager;
};
