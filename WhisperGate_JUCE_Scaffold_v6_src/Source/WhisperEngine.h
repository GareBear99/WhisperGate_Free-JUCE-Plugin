#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>
class WhisperEngine
{
public:
    void prepare (const juce::dsp::ProcessSpec& spec);
    void reset();
    void process (juce::AudioBuffer<float>& buffer,float whisper,float breath,float drift,float presence,float echo,float temple,float width,float choir,float dryWet);
private:
    juce::dsp::StateVariableTPTFilter<float> filterL, filterR;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayL { 44100 };
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayR { 44100 };
    juce::Random random;
    double sampleRate = 44100.0;
};
