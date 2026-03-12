#include "PluginProcessor.h"
#include "PluginEditor.h"
WhisperGateLiteAudioProcessor::WhisperGateLiteAudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
{
    codexStateManager.addEntry({"Lurking Choir","haunted",0.72f});
    codexStateManager.addEntry({"Temple Hiss","space",0.56f});
    sequenceEngine.addStep({"One",0.42f,0xffaa3344});
    sequenceEngine.addStep({"Two",0.77f,0xffdd7744});
}
juce::AudioProcessorValueTreeState::ParameterLayout WhisperGateLiteAudioProcessor::createParameterLayout()
{
    using AP = juce::AudioParameterFloat;
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    auto add=[&params](const juce::String& id,const juce::String& name,float min,float max,float def){ params.push_back(std::make_unique<AP>(id,name,juce::NormalisableRange<float>(min,max),def)); };
    add(ParamIDs::output,"Output",0.0f,1.0f,0.70f); add(ParamIDs::dryWet,"DryWet",0.0f,1.0f,0.60f); add(ParamIDs::whisper,"Whisper",0.0f,1.0f,0.70f);
    add(ParamIDs::breath,"Breath",0.0f,1.0f,0.52f); add(ParamIDs::drift,"Drift",0.0f,1.0f,0.46f); add(ParamIDs::presence,"Presence",0.0f,1.0f,0.35f);
    add(ParamIDs::echo,"Echo",0.0f,1.0f,0.42f); add(ParamIDs::temple,"Temple",0.0f,1.0f,0.62f); add(ParamIDs::width,"Width",0.0f,1.0f,0.55f);
    add(ParamIDs::choir,"Choir",0.0f,1.0f,0.28f); add(ParamIDs::phraseRate,"PhraseRate",0.0f,1.0f,0.50f); add(ParamIDs::phraseLen,"PhraseLen",0.0f,1.0f,0.45f);
    add(ParamIDs::randomness,"Randomness",0.0f,1.0f,0.30f); add(ParamIDs::uiSfxLevel,"UISfxLevel",0.0f,1.0f,0.25f); add(ParamIDs::ritualMacro,"RitualMacro",0.0f,1.0f,0.50f);
    return {params.begin(), params.end()};
}
void WhisperGateLiteAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec{sampleRate, (juce::uint32)samplesPerBlock, 2}; whisperEngine.prepare(spec);
}
void WhisperGateLiteAudioProcessor::releaseResources(){}
bool WhisperGateLiteAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono() || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
void WhisperGateLiteAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals; buffer.clear();
    auto get=[this](const char* id){ return apvts.getRawParameterValue(id)->load(); };
    whisperEngine.process(buffer,get(ParamIDs::whisper),get(ParamIDs::breath),get(ParamIDs::drift),get(ParamIDs::presence),get(ParamIDs::echo),get(ParamIDs::temple),get(ParamIDs::width),get(ParamIDs::choir),get(ParamIDs::dryWet));
    buffer.applyGain(get(ParamIDs::output)); uiSfxEngine.setLevel(get(ParamIDs::uiSfxLevel)); cachedCombos = comboEngine.evaluate(runeManager);
}
float WhisperGateLiteAudioProcessor::computeRitualCharge() const
{
    auto get=[this](const char* id){ return apvts.getRawParameterValue(id)->load(); };
    float charge=0.0f; charge += 0.16f * (float)runeManager.getActiveCount() / 9.0f; charge += 0.12f * get(ParamIDs::whisper); charge += 0.10f * get(ParamIDs::breath);
    charge += 0.09f * get(ParamIDs::drift); charge += 0.08f * get(ParamIDs::presence); charge += 0.11f * get(ParamIDs::echo); charge += 0.12f * get(ParamIDs::temple);
    charge += 0.08f * get(ParamIDs::width); charge += 0.08f * get(ParamIDs::choir); charge += comboEngine.computeComboBonus(cachedCombos);
    return juce::jlimit(0.0f,1.0f,charge);
}
RuneComboEngine::ComboFlags WhisperGateLiteAudioProcessor::getComboFlags(){ cachedCombos = comboEngine.evaluate(runeManager); return cachedCombos; }
juce::AudioProcessorEditor* WhisperGateLiteAudioProcessor::createEditor(){ return new WhisperGateLiteAudioProcessorEditor(*this); }
void WhisperGateLiteAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState(); if (auto xml = state.createXml()) copyXmlToBinary(*xml, destData);
}
void WhisperGateLiteAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName(apvts.state.getType())) apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}
