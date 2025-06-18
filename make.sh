#!/bin/bash
set -e

cmake --build ./build --config Release
sudo cp -a build/Setekh_artefacts/Release/VST3/Setekh.vst3 /Library/Audio/Plug-Ins/VST3/
