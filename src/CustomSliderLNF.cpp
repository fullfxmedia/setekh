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
    }
}

void CustomSliderLNF::drawLinearSliderThumb(juce::Graphics& g,
                                            int x, int y, int width, int height,
                                            float sliderPos,
                                            float minSliderPos,
                                            float maxSliderPos,
                                            const juce::Slider::SliderStyle style,
                                            juce::Slider& slider)
{
    // Custom drawing code for the linear slider thumb
    g.setColour (juce::Colours::blue);
    g.fillEllipse (x, y, width, height);
}
