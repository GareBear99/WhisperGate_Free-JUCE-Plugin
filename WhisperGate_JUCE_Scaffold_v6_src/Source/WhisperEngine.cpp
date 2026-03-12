#include "WhisperEngine.h"
void WhisperEngine::prepare (const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    filterL.prepare(spec); filterR.prepare(spec);
    filterL.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    filterR.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    delayL.prepare(spec); delayR.prepare(spec); reset();
}
void WhisperEngine::reset(){ filterL.reset(); filterR.reset(); delayL.reset(); delayR.reset(); }
void WhisperEngine::process (juce::AudioBuffer<float>& buffer,float whisper,float breath,float drift,float presence,float echo,float temple,float width,float choir,float dryWet)
{
    const auto numSamples = buffer.getNumSamples();
    const auto numChannels = juce::jmin(2, buffer.getNumChannels());
    const float centreFreq = 500.0f + drift * 2600.0f + presence * 1400.0f;
    filterL.setCutoffFrequency(centreFreq); filterR.setCutoffFrequency(centreFreq * (1.0f + 0.02f * width));
    const float feedback = 0.10f + echo * 0.55f;
    const float wet = juce::jlimit(0.0f,1.0f,dryWet), dry = 1.0f - wet;
    for (int s=0; s<numSamples; ++s)
    {
        const float n = (random.nextFloat()*2.0f - 1.0f);
        const float whisperSample = n * (0.02f + whisper*0.08f + breath*0.04f);
        float l = filterL.processSample(0, whisperSample);
        float r = filterR.processSample(1, whisperSample * (1.0f - 0.03f * choir));
        const auto delayedL = delayL.popSample(0, 220 + (int)(temple * 1400.0f));
        const auto delayedR = delayR.popSample(0, 340 + (int)(temple * 2200.0f));
        delayL.pushSample(0, l + delayedR * feedback); delayR.pushSample(0, r + delayedL * feedback);
        l = dry * l + wet * (l + delayedL * 0.5f); r = dry * r + wet * (r + delayedR * 0.5f);
        if(numChannels > 0) buffer.addSample(0, s, l);
        if(numChannels > 1) buffer.addSample(1, s, r);
    }
}
