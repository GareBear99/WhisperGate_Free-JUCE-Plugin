#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"
#include "VisualRenderer.h"
#include "CodexDrawerComponent.h"
#include "SequenceArcComponent.h"
#include "UIEventRouter.h"
class WhisperGateLiteAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit WhisperGateLiteAudioProcessorEditor (WhisperGateLiteAudioProcessor&);
    ~WhisperGateLiteAudioProcessorEditor() override = default;
    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseMove (const juce::MouseEvent&) override;
    void mouseDown (const juce::MouseEvent&) override;
    void mouseDrag (const juce::MouseEvent&) override;
    void mouseUp (const juce::MouseEvent&) override;
private:
    void timerCallback() override;
    void refreshRingValues();
    RuneId hitTestRune (juce::Point<float> p) const;
    int hitTestRing (juce::Point<float> p) const;
    WhisperGateLiteAudioProcessor& processor;
    VisualRenderer renderer;
    CodexDrawerComponent codexDrawer;
    SequenceArcComponent sequenceArc;
    UIEventRouter eventRouter;
    bool codexVisible=false;
    int draggedRing=-1;
    std::array<float,7> ringValues{0.5f,0.45f,0.35f,0.55f,0.30f,0.60f,0.40f};
    juce::TextButton codexButton{"Codex"};
};
