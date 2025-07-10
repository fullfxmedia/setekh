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
        int frameWidth = knobImage.getWidth();
        int frameHeight = knobImage.getHeight() / numFrames;
        int frameIndex = juce::jlimit(0, numFrames - 1,
                                      static_cast<int>(sliderPosProportional * (numFrames - 1)));
        float scale = std::min(width / (float)frameWidth, height / (float)frameHeight);
        int scaledWidth = static_cast<int>(frameWidth * scale);
        int scaledHeight = static_cast<int>(frameHeight * scale);

        // Center the knob in the available space
        int destX = x + (width - scaledWidth) / 2;
        int destY = y + (height - scaledHeight) / 2;

        g.drawImage(knobImage,
                    destX, destY, scaledWidth, scaledHeight,
                    0, frameIndex * frameHeight,
                    frameWidth, frameHeight);
    }
}

