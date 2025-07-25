//
// Copyright (c) 2025 Full FX Media
//

#include "CustomSliderLNF.h"

CustomSliderLNF::CustomSliderLNF()
{
    loadFilmstripImages();
}

CustomSliderLNF::~CustomSliderLNF()
{
}

void CustomSliderLNF::loadFilmstripImages()
{
    inputGainFilmstrip = juce::ImageCache::getFromMemory(BinaryData::input_gain_slider_png,
                                                        BinaryData::input_gain_slider_pngSize);
    outputGainFilmstrip = juce::ImageCache::getFromMemory(BinaryData::output_gain_slider_png,
                                                         BinaryData::output_gain_slider_pngSize);
    
    // Debug: Check if images loaded successfully
    DBG("Input gain filmstrip loaded: " << inputGainFilmstrip.isValid() <<
        " (" << inputGainFilmstrip.getWidth() << "x" << inputGainFilmstrip.getHeight() << ")");
    DBG("Output gain filmstrip loaded: " << outputGainFilmstrip.isValid() <<
        " (" << outputGainFilmstrip.getWidth() << "x" << outputGainFilmstrip.getHeight() << ")");
}

void CustomSliderLNF::setSliderType(SliderType type)
{
    currentSliderType = type;
}

const juce::Image& CustomSliderLNF::getCurrentFilmstrip() const
{
    switch (currentSliderType)
    {
        case InputGain:
            return inputGainFilmstrip;
        case OutputGain:
            return outputGainFilmstrip;
        default:
            return inputGainFilmstrip;
    }
}

void CustomSliderLNF::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                                      float sliderPos, float minSliderPos, float maxSliderPos,
                                      const juce::Slider::SliderStyle style,
                                      juce::Slider& slider)
{
    const juce::Image& filmstrip = getCurrentFilmstrip();
    
    if (filmstrip.isValid())
    {
        // Calculate which frame to show based on slider position
        float normalizedValue = (sliderPos - minSliderPos) / (maxSliderPos - minSliderPos);
        
        // Invert for vertical sliders (top = max value)
        if (style == juce::Slider::LinearVertical)
            normalizedValue = 1.0f - normalizedValue;
            
        int frameIndex = juce::jlimit(0, numFrames - 1, (int)(normalizedValue * (numFrames - 1)));
        
        // Each frame is the full width of the filmstrip, height is total height / numFrames
        int frameWidth = filmstrip.getWidth();
        int frameHeight = filmstrip.getHeight() / numFrames;
        
        // Calculate source rectangle for the current frame
        juce::Rectangle<int> sourceRect(0, frameIndex * frameHeight, frameWidth, frameHeight);
        
        // Draw the frame, scaled to fit the slider bounds
        juce::Rectangle<int> destRect(x, y, width, height);
        g.drawImage(filmstrip, destRect, sourceRect);
    }
    else
    {
        // Fallback to default slider drawing if image fails to load
        juce::LookAndFeel_V4::drawLinearSlider(g, x, y, width, height, sliderPos, 
                                              minSliderPos, maxSliderPos, style, slider);
        
        // Draw a simple error indicator
        g.setColour(juce::Colours::red);
        g.drawRect(x, y, width, height, 2);
        g.setColour(juce::Colours::white);
        g.drawText("IMG ERR", x, y, width, height, juce::Justification::centred);
    }
}