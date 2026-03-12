#include "SigilStateManager.h"
juce::ValueTree SigilStateManager::createEmptyState() const
{
    juce::ValueTree root("WhisperGateState");
    root.setProperty("name","Untitled Sigil",nullptr);
    root.setProperty("seed","abyss-01",nullptr);
    root.setProperty("ritualCharge",0.0f,nullptr);
    root.setProperty("timestamp",juce::Time::getCurrentTime().toISO8601(true),nullptr);
    return root;
}
juce::String SigilStateManager::toJson (const juce::ValueTree& state) const
{
    if (auto* xml = state.createXml()) return xml->toString();
    return {};
}
juce::ValueTree SigilStateManager::fromJson (const juce::String& text) const
{
    std::unique_ptr<juce::XmlElement> xml(juce::parseXML(text));
    if(xml==nullptr) return {};
    return juce::ValueTree::fromXml(*xml);
}
