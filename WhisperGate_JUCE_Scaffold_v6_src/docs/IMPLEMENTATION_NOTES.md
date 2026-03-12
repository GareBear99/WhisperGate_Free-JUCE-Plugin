# Implementation Notes

## Visual system
The current renderer uses pure JUCE Graphics so it stays portable.
For the final premium pass you may move the FX layer to OpenGLRenderer, custom shaders, or cached particle atlases.

## DSP
Current `WhisperEngine` is intentionally lightweight and placeholder-grade.
The production engine should add:
- parallel formant bands
- better breath/noise coloration
- optional choir duplication and random spread
- safer echo/room topology
- CPU-limited voice strategy
