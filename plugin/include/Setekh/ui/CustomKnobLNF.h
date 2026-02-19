//
// Copyright (c) 2025 Full FX Media
//

#pragma once

#include <JuceHeader.h>

class CustomKnobLNF : public juce::LookAndFeel_V4 {
public:
    CustomKnobLNF();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider& slider) override;

private:
    juce::Image knobImage;
    int numFrames;
    juce::Font labelFont;
};