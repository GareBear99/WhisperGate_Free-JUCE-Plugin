# WhisperGate

> 🎛️ **Part of the [TizWildin Plugin Ecosystem](https://garebear99.github.io/TizWildinEntertainmentHUB/)** — 14 free audio plugins with a live update dashboard.
>
> [FreeEQ8](https://github.com/GareBear99/FreeEQ8) · [Instrudio](https://github.com/GareBear99/Instrudio) · [BassMaid](https://github.com/GareBear99/BassMaid) · [SpaceMaid](https://github.com/GareBear99/SpaceMaid) · [GlueMaid](https://github.com/GareBear99/GlueMaid) · [MixMaid](https://github.com/GareBear99/MixMaid) · [ChainMaid](https://github.com/GareBear99/ChainMaid) · [PaintMask](https://github.com/GareBear99/PaintMask_Free-JUCE-Plugin) · [WURP](https://github.com/GareBear99/WURP_Toxic-Motion-Engine_JUCE) · [AETHER](https://github.com/GareBear99/AETHER_Choir-Atmosphere-Designer) · [WhisperGate](https://github.com/GareBear99/WhisperGate_Free-JUCE-Plugin) · [Therum](https://github.com/GareBear99/Therum_JUCE-Plugin) · [RiftWave](https://github.com/GareBear99/RiftWaveSuite_RiftSynth_WaveForm_Lite) · [FreeSampler](https://github.com/GareBear99/FreeSampler_v0.3)


### Ritual Whisper Instrument

WhisperGate Lite is an experimental audio plugin that transforms sound into **procedural whispers, ghost choirs, and ritual atmospheres** through an interactive geometry interface.

Instead of knobs and sliders, WhisperGate uses **runes, rings, and sigils** to control sound.

The goal is simple:

> Make a plugin that feels like an **instrument or ritual device**, not software.

---

## Philosophy

WhisperGate Lite is **100% free**.

You can:

- download it  
- fork it  
- modify it  
- compile it  
- steal it  

If it helps you make something cool, consider donating **$1 for a coffee**.

No DRM.  
No license servers.  
No nonsense.

---

## Features

### Ritual Geometry Interface
Control the engine using **concentric rings and rune activators** instead of traditional plugin UI controls.

### Procedural Whisper Engine
Generates layered whisper textures with:

- breath noise
- formant shaping
- drift instability
- spectral bite

### Choir Layer
Duplicate and spatialize voices into eerie stacked choirs.

### Echo Field
Ritual repeat engine with ghost trails.

### Temple Reverb
Large chamber and corridor reverbs designed for atmospheric sound design.

### Floating Rune FX
Visual particles respond to the **global ritual charge** created by your sound.

### Sigil Presets
States are saved as **visual sigils** rather than traditional preset lists.

### Sequence Arc
Create evolving whisper patterns by sequencing sigil states.

### Addon Ready
The engine supports external rune packs and visual themes.

---

## Current Status

WhisperGate Lite is currently provided as a **JUCE source scaffold**.

Included:

- plugin architecture
- rune state system
- sequence engine
- sigil state manager
- visual renderer
- GUI components
- addon framework

The project is designed to compile into:

- VST3
- AU
- Standalone

---

## Build Requirements

To compile WhisperGate Lite you need:

- JUCE framework
- CMake
- modern C++ compiler

Typical build flow:


git clone https://github.com/YOURNAME/WhisperGateLite.git

cd WhisperGateLite
mkdir build
cd build
cmake ..
cmake --build .


Then load the compiled plugin in your DAW.

---

## Folder Structure


WhisperGateLite
│
├─ Source
│ ├─ DSP
│ ├─ GUI
│ ├─ RuneSystem
│ ├─ VisualFX
│ └─ Sequencer
│
├─ Resources
│ ├─ glyphs
│ ├─ shaders
│ └─ ui_sfx
│
├─ presets
├─ addons
├─ docs
└─ builds


---

## Addon System

The plugin supports custom rune packs and themes.

Example structure:


addons/
agartha/
runes.json
visuals.json
presets.json


Future packs can add:

- new runes
- new sigil themes
- visual styles
- sequence packs

---

## Why This Exists

Most audio plugins follow the same pattern:


knobs
sliders
preset list


WhisperGate asks a different question:

> What if a plugin looked and behaved like an **occult instrument**?

This project explores that idea.

---

## Donate

If WhisperGate helps you make music or sound design you like, you can support development:

☕ Buy me a coffee

(coming soon)

---

## License

Free to use, modify, and experiment with.

Just don’t take the exact build and resell it unchanged.

---

## Roadmap

Planned improvements:

- production DSP whisper engine
- optimized renderer
- expanded rune combos
- cinematic UI SFX
- official addon packs
- compiled releases

---

## Author

Gary Doman

Builder of experimental audio tools and strange interfaces.
