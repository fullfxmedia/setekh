//
// Copyright (c) 2025 Full FX Media
//

#include "CustomSliderLNF.h"
#include <iostream>

CustomSliderLNF::CustomSliderLNF()
{
    inputSliderImage = juce::ImageCache::getFromMemory(BinaryData::input_slider_png,
                                                    BinaryData::input_slider_pngSize);
    outputSliderImage = juce::ImageCache::getFromMemory(BinaryData::output_slider_png,
                                                         BinaryData::output_slider_pngSize);
    gainSliderThumbImage = juce::ImageCache::getFromMemory(BinaryData::gain_slider_png,
                                                          BinaryData::gain_slider_pngSize);
}

CustomSliderLNF::~CustomSliderLNF()
{
}

void CustomSliderLNF::setSliderType(SliderType type)
{
    currentSliderType = type;
}

void CustomSliderLNF::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                                      float sliderPos, float minSliderPos, float maxSliderPos,
                                      const juce::Slider::SliderStyle style,
                                      juce::Slider& slider)
{
    std::cout << "drawLinearSlider called for slider type: " << (currentSliderType == InputGain ? "InputGain" : "OutputGain") << std::endl;

    // Draw the background track
    g.setColour(juce::Colours::darkgrey);
    g.fillRoundedRectangle(x, y, width, height, 4.0f);

    // Draw the value bar
    g.setColour(juce::Colours::lightgrey);
    if (style == juce::Slider::SliderStyle::LinearVertical)
    {
        // The bar starts from the bottom and goes up to the slider position
        g.fillRoundedRectangle((float)x, sliderPos, (float)width, (float)(y + height) - sliderPos, 4.0f);
    }
    else
    {
        // The bar starts from the left and goes to the slider position
        g.fillRoundedRectangle((float)x, (float)y, sliderPos - x, (float)height, 4.0f);
    }

    drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
}

void CustomSliderLNF::drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height,
                                           float sliderPos, float minSliderPos, float maxSliderPos,
                                           const juce::Slider::SliderStyle style,
                                           juce::Slider& slider)
{
    std::cout << "=== drawLinearSliderThumb called ===" << std::endl;

    if (gainSliderThumbImage.isValid())
    {
        // Use the original image dimensions to preserve shape and size
        int thumbWidth = gainSliderThumbImage.getWidth();
        int thumbHeight = gainSliderThumbImage.getHeight();

        // Calculate the actual slider value range for proper positioning
        double currentValue = slider.getValue();
        double minValue = slider.getMinimum();
        double maxValue = slider.getMaximum();

        // Calculate normalized position based on actual slider values (0.0 to 1.0)
        float normalizedValue = (float)((currentValue - minValue) / (maxValue - minValue));

        // For vertical sliders, invert the position (top = max value)
        if (style == juce::Slider::LinearVertical)
            normalizedValue = 1.0f - normalizedValue;

        std::cout << "Value: " << currentValue << ", Normalized: " << normalizedValue << std::endl;

        // Calculate thumb position with proper bounds
        int availableTrackHeight = height - thumbHeight;
        int thumbY = y + (int)(normalizedValue * availableTrackHeight);
        int thumbX = x + (width - thumbWidth) / 2;

        // Ensure thumb stays within bounds
        thumbY = juce::jlimit(y, y + height - thumbHeight, thumbY);
        thumbX = juce::jlimit(x, x + width - thumbWidth, thumbX);

        std::cout << "Drawing thumb at: " << thumbX << ", " << thumbY << std::endl;

        // Draw the custom thumb at original size (no scaling)
        g.setImageResamplingQuality(Graphics::highResamplingQuality);
        g.drawImageAt(gainSliderThumbImage, thumbX, thumbY);
    }
    else
    {
        std::cout << "Using fallback thumb" << std::endl;

        // Fallback: draw a bright visible thumb
        int thumbWidth = width - 4;
        int thumbHeight = 20;

        float normalizedValue = (sliderPos - minSliderPos) / (maxSliderPos - minSliderPos);
        if (style == juce::Slider::LinearVertical)
            normalizedValue = 1.0f - normalizedValue;

        int thumbY = y + (int)(normalizedValue * (height - thumbHeight));
        int thumbX = x + 2;

        thumbY = juce::jlimit(y, y + height - thumbHeight, thumbY);

        // Draw bright fallback thumb
        g.setColour(juce::Colours::yellow);
        g.fillRoundedRectangle(thumbX, thumbY, thumbWidth, thumbHeight, 4.0f);
        g.setColour(juce::Colours::red);
        g.drawRoundedRectangle(thumbX, thumbY, thumbWidth, thumbHeight, 4.0f, 2.0f);
    }
}