# Setekh

A minimalistic yet sonically powerful distortion plugin created and distributed via Full FX Media.

## About

[Set](<https://en.wikipedia.org/wiki/Set_(deity)>) is a god of deserts, storms, disorder, violence, and foreigners in ancient Egyptian religion

## Build

```bash
git clone --recurse-submodules https://github.com/tiagolr/ripplerx.git

# OSX
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURE="x86_64;arm64" -S . -B ./build
cmake --build ./build --config Release
sudo cp -a build/Setekh_artefacts/Release/VST3/Setekh.vst3 /Library/Audio/Plug-Ins/VST3/
```
