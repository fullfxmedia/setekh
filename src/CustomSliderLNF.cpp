//
// Copyright (c) 2025 Full FX Media
//

#include "CustomSliderLNF.h"

CustomSliderLNF::CustomSliderLNF()
{
    inputSliderImage = juce::ImageCache::getFromMemory(BinaryData::input_slider_png,
                                                    BinaryData::input_slider_pngSize);
    outputSliderImage = juce::ImageCache::getFromMemory(BinaryData::output_slider_png,
                                                         BinaryData::output_slider_pngSize);
    gainSliderThumbImage = juce::ImageCache::getFromMemory(BinaryData::gain_slider_png,
                                                          BinaryData::gain_slider_pngSize);

    // Debug: Check if images loaded successfully
    DBG("Input gain background loaded: " << inputSliderImage.isValid() <<
        " (" << inputSliderImage.getWidth() << "x" << inputSliderImage.getHeight() << ")");
    DBG("Output gain background loaded: " << outputSliderImage.isValid() <<
        " (" << outputSliderImage.getWidth() << "x" << outputSliderImage.getHeight() << ")");
    DBG("Gain slider thumb loaded: " << gainSliderThumbImage.isValid() <<
        " (" << gainSliderThumbImage.getWidth() << "x" << gainSliderThumbImage.getHeight() << ")");
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
    // Get the appropriate background image based on slider type
    const juce::Image& backgroundImg = (currentSliderType == InputGain) ? inputSliderImage : outputSliderImage;

    if (backgroundImg.isValid())
    {
        // Draw the background slider track
        g.drawImage(backgroundImg, x, y, width, height,
                   0, 0, backgroundImg.getWidth(), backgroundImg.getHeight());

        // Draw the custom thumb if the thumb image is valid
        if (gainSliderThumbImage.isValid())
        {
            // Calculate thumb dimensions
            int thumbWidth = juce::jmin(width - 4, gainSliderThumbImage.getWidth());
            int thumbHeight = juce::jmin(20, gainSliderThumbImage.getHeight());

            // Calculate normalized position (0.0 to 1.0)
            float normalizedValue = (sliderPos - minSliderPos) / (maxSliderPos - minSliderPos);

            if (style == juce::Slider::LinearVertical)
                normalizedValue = 1.0f - normalizedValue;

            // Calculate thumb position
            int thumbY = y + (int)(normalizedValue * (height - thumbHeight));
            int thumbX = x + (width - thumbWidth) / 2;

            // Ensure thumb stays within bounds
            thumbY = juce::jlimit(y, y + height - thumbHeight, thumbY);

            // Draw the custom thumb
            g.drawImage(gainSliderThumbImage, thumbX, thumbY, thumbWidth, thumbHeight,
                       0, 0, gainSliderThumbImage.getWidth(), gainSliderThumbImage.getHeight());
        }
        else
        {
            // Fallback: draw a simple thumb if custom image fails
            drawSimpleThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style);
        }
    }
    else
    {
        // Fallback to default slider drawing if background image fails to load
        juce::LookAndFeel_V4::drawLinearSlider(g, x, y, width, height, sliderPos,
                                              minSliderPos, maxSliderPos, style, slider);

        // Draw error indicator
        g.setColour(juce::Colours::red);
        g.drawRect(x, y, width, height, 2);
        g.setColour(juce::Colours::white);
        g.drawText("IMG ERR", x, y, width, height, juce::Justification::centred);
    }
}

void CustomSliderLNF::drawSimpleThumb(juce::Graphics& g, int x, int y, int width, int height,
                                     float sliderPos, float minSliderPos, float maxSliderPos,
                                     const juce::Slider::SliderStyle style)
{
    // Simple fallback thumb
    int thumbWidth = width - 4;
    int thumbHeight = 12;

    float normalizedValue = (sliderPos - minSliderPos) / (maxSliderPos - minSliderPos);
    if (style == juce::Slider::LinearVertical)
        normalizedValue = 1.0f - normalizedValue;

    int thumbY = y + (int)(normalizedValue * (height - thumbHeight));
    int thumbX = x + 2;

    thumbY = juce::jlimit(y, y + height - thumbHeight, thumbY);

    // Draw simple rectangular thumb
    g.setColour(juce::Colours::lightgrey);
    g.fillRoundedRectangle(thumbX, thumbY, thumbWidth, thumbHeight, 2.0f);
    g.setColour(juce::Colours::darkgrey);
    g.drawRoundedRectangle(thumbX, thumbY, thumbWidth, thumbHeight, 2.0f, 1.0f);
}