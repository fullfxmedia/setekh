//
// Copyright (c) 2025 Full FX Media
//

#include "CustomKnobLNF.h"

CustomKnobLNF::CustomKnobLNF() {
    knobImage = juce::ImageCache::getFromMemory(BinaryData::drive_knob_png, BinaryData::drive_knob_pngSize);
    numFrames = 128;
}

void CustomKnobLNF::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                                     float sliderPosProportional, float, float, juce::Slider&) {
    if (knobImage.isValid()) {
        int frameHeight = knobImage.getHeight() / numFrames;
        int frameIndex = juce::jlimit(0, numFrames - 1,
                                      static_cast<int>(sliderPosProportional * (numFrames - 1)));

        g.drawImage(knobImage,
                    x, y, width, height,
                    0, frameIndex * frameHeight,
                    knobImage.getWidth(), frameHeight);
    }
}

