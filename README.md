# Setekh

A minimalistic yet sonically powerful distortion plugin created and distributed via Full FX Media.

This is a C++ audio plugin project utilizing the JUCE framework. The build system is CMake.

## About

[Set](<https://en.wikipedia.org/wiki/Set_(deity)>) is a god of deserts, storms, disorder, violence, and foreigners in ancient Egyptian religion

## Build

```bash
git clone --recurse-submodules https://github.com/tiagolr/ripplerx.git

# OSX
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64" -S . -B ./build
cmake --build ./build --config Release
```

Clean target:

```bash
cmake --build ./build --target clean --config Release
```

Refresh BinaryData/resources folder:
```bash
cd build
cmake ..
make clean
make
```

## Mockup

<img src="docs/mockup.png" alt="drawing" width="400"/>

---

# Key Files

- `CMakeLists.txt`: The main CMake build configuration file.
- `src/PluginProcessor.h` & `src/PluginProcessor.cpp`: Core audio processing logic.
- `src/PluginEditor.h` & `src/PluginEditor.cpp`: Plugin UI implementation.
- `src/CustomKnobLNF.h` & `src/CustomSliderLNF.h`: Custom "Look and Feel" classes for UI elements, indicating a convention for custom styling.
- `.github/workflows/build.yml`: Defines the CI build process, a good reference for build commands.

# How to Build

The project uses CMake. The standard build process is likely:

1.  **Configure:** `cmake -B build`
2.  **Build:** `cmake --build build`

The `make.sh` script is also present and may provide a simplified build method. I will inspect it before using it. For the canonical build process, I will refer to `.github/workflows/build.yml`.

# Code Style and Conventions

The code appears to follow standard JUCE/C++ conventions. UI components seem to be styled using custom LookAndFeel (`LNF`) classes, and I will follow this pattern for any new UI work.

---
