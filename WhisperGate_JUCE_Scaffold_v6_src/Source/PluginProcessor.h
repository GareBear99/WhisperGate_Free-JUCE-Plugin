#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "WhisperEngine.h"
#include "RuneManager.h"
#include "RuneComboEngine.h"
#include "SequenceEngine.h"
#include "SigilStateManager.h"
#include "CodexStateManager.h"
#include "UISfxEngine.h"
#include "ParameterIDs.h"
class WhisperGateLiteAudioProcessor : public juce::AudioProcessor
{
public:
    WhisperGateLiteAudioProcessor();
    ~WhisperGateLiteAudioProcessor() override = default;
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return "WhisperGate Lite"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 2.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}
    void getStateInformation (juce::MemoryBlock&) override;
    void setStateInformation (const void*, int) override;
    juce::AudioProcessorValueTreeState apvts;
    RuneManager runeManager;
    RuneComboEngine comboEngine;
    SequenceEngine sequenceEngine;
    SigilStateManager sigilStateManager;
    CodexStateManager codexStateManager;
    UISfxEngine uiSfxEngine;
    float computeRitualCharge() const;
    RuneComboEngine::ComboFlags getComboFlags();
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
private:
    WhisperEngine whisperEngine;
    RuneComboEngine::ComboFlags cachedCombos;
};
