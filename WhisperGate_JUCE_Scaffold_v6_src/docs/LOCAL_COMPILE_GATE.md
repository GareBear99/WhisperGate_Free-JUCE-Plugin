# Local Compile Gate

## macOS example
```bash
cmake -S . -B build -DJUCE_DIR=/path/to/JUCE
cmake --build build --config Release
```

## Completion checklist
- configure succeeds
- project builds in Release
- Standalone opens
- AU validates
- VST3 loads in host
- no asserts when toggling runes / dragging rings
