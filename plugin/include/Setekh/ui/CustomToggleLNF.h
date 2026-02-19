//
// Copyright (c) 2025 Full FX Media
//

#pragma once

#include <JuceHeader.h>

class CustomToggleLNF : public juce::LookAndFeel_V4
{
public:
    CustomToggleLNF();
    ~CustomToggleLNF() override = default;

    void drawToggleButton (juce::Graphics& g,
                          juce::ToggleButton& button,
                          bool shouldDrawButtonAsHighlighted,
                          bool shouldDrawButtonAsDown) override;

private:
    juce::Image toggleOn;
    juce::Image toggleOff;
};