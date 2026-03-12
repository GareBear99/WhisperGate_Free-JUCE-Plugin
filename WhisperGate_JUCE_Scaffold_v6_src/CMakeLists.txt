cmake_minimum_required(VERSION 3.22)
project(WhisperGateLite VERSION 0.5.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(DEFINED JUCE_DIR)
    add_subdirectory(${JUCE_DIR} JUCE)
else()
    message(FATAL_ERROR "Set JUCE_DIR to your JUCE checkout before configuring.")
endif()

juce_add_plugin(WhisperGateLite
    COMPANY_NAME "Gary Doman"
    BUNDLE_ID "com.garydoman.whispergatelite"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE GdOm
    PLUGIN_CODE WgLt
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "WhisperGate Lite")

target_sources(WhisperGateLite PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEntry.cpp
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/ParameterIDs.h
    Source/RuneManager.cpp
    Source/RuneManager.h
    Source/RuneComboEngine.cpp
    Source/RuneComboEngine.h
    Source/SequenceEngine.cpp
    Source/SequenceEngine.h
    Source/SigilStateManager.cpp
    Source/SigilStateManager.h
    Source/CodexStateManager.cpp
    Source/CodexStateManager.h
    Source/UIEventRouter.cpp
    Source/UIEventRouter.h
    Source/UISfxEngine.cpp
    Source/UISfxEngine.h
    Source/VisualRenderer.cpp
    Source/VisualRenderer.h
    Source/CodexDrawerComponent.cpp
    Source/CodexDrawerComponent.h
    Source/SequenceArcComponent.cpp
    Source/SequenceArcComponent.h
    Source/WhisperEngine.cpp
    Source/WhisperEngine.h)

target_compile_definitions(WhisperGateLite PUBLIC JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0 JUCE_VST3_CAN_REPLACE_VST2=0)
target_link_libraries(WhisperGateLite PRIVATE juce::juce_audio_utils juce::juce_dsp juce::juce_gui_extra
    PUBLIC juce::juce_recommended_config_flags juce::juce_recommended_warning_flags)
