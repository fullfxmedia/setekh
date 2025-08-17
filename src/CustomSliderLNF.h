//
// Copyright (c) 2025 Full FX Media
//

#pragma once

#include <JuceHeader.h>

class CustomSliderLNF : public juce::LookAndFeel_V4
{
public:
    enum SliderType
    {
        InputGain,
        OutputGain
    };

    CustomSliderLNF();
    ~CustomSliderLNF() override;

    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                         float sliderPos, float minSliderPos, float maxSliderPos,
                         const juce::Slider::SliderStyle style,
                         juce::Slider& slider) override;

    juce::Font getLabelFont (juce::Label& label) override;

    void drawLabel (juce::Graphics& g, juce::Label& label) override;

    // Method to set which slider type this instance should render
    void setSliderType(SliderType type);

    void drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height,
                               float sliderPos, float minSliderPos, float maxSliderPos,
                               const juce::Slider::SliderStyle style,
                               juce::Slider& slider) override;

private:
    SliderType currentSliderType = InputGain;

    // Images
    juce::Image gainSliderThumbImage;
    juce::Font labelFont;
};