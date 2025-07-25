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

    // Method to set which slider type this instance should render
    void setSliderType(SliderType type);

    // Method to load filmstrip images
    void loadFilmstripImages();

private:
    SliderType currentSliderType = InputGain;
    juce::Image inputGainFilmstrip;
    juce::Image outputGainFilmstrip;
    static constexpr int numFrames = 128;

    // Helper method to get the appropriate image for current slider type
    const juce::Image& getCurrentFilmstrip() const;
};