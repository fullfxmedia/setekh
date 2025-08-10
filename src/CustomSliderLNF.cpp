//
// Copyright (c) 2025 Full FX Media
//

#include "CustomSliderLNF.h"
#include "BinaryData.h"

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
    if (style == juce::Slider::LinearVertical)
    {
        const int thumbHeight = 56;
        const int halfThumbHeight = thumbHeight / 2;
        const int trackWidth = 8; // Make the slider track narrower

        const int trackX = x + (width - trackWidth) / 2;
        const int trackY = y + halfThumbHeight;
        const int trackHeight = height - thumbHeight;

        // Draw the background track
        g.setColour(juce::Colour::fromRGB(0x25, 0x25, 0x25));
        g.fillRoundedRectangle((float)trackX, (float)trackY, (float)trackWidth, (float)trackHeight, 4.0f);

        // Draw the value bar
        const float normalizedValue = (float)((slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum()));
        const float barTop = trackY + (1.0f - normalizedValue) * trackHeight;
        const float barHeight = (float)(trackY + trackHeight) - barTop;

        g.fillRoundedRectangle((float)trackX, barTop, (float)trackWidth, barHeight, 4.0f);

        // Draw labels
        auto roboto = juce::Typeface::createSystemTypefaceFor(
            BinaryData::RobotoRegular_ttf,
            BinaryData::RobotoRegular_ttfSize
        );
        g.setFont(juce::Font(roboto));
        g.setFont(12.0f);
        g.setColour(juce::Colours::white);

        const float labels[] = { -24.0f, -12.0f, 0.0f, 12.0f, 24.0f };
        const int numLabels = sizeof(labels) / sizeof(labels[0]);

        for (int i = 0; i < numLabels; ++i)
        {
            float value = labels[i];
            float normalizedLabelValue = (value - (float)slider.getMinimum()) / ((float)slider.getMaximum() - (float)slider.getMinimum());
            float labelY = trackY + (1.0f - normalizedLabelValue) * trackHeight;

            juce::String labelText = juce::String(value, 0) + "db";

            int textWidth = g.getCurrentFont().getStringWidth(labelText);
            int labelX;

            if (currentSliderType == InputGain)
            {
                labelX = trackX - textWidth - 15;
            }
            else // OutputGain
            {
                labelX = trackX + trackWidth + 15;
            }

            g.drawText(labelText, labelX, (int)labelY - 6, textWidth, 12, juce::Justification::centredLeft);
        }
    }
    else // Horizontal
    {
        const int trackHeight = 8;
        const int trackY = y + (height - trackHeight) / 2;
        g.setColour(juce::Colour(0xff252525));
        g.fillRoundedRectangle((float)x, (float)trackY, (float)width, (float)trackHeight, 4.0f);

        const float barWidth = sliderPos - x;
        g.setColour(juce::Colours::lightgrey);
        g.fillRoundedRectangle((float)x, (float)trackY, barWidth, (float)trackHeight, 4.0f);
    }

    drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
}

void CustomSliderLNF::drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height,
                                           float sliderPos, float minSliderPos, float maxSliderPos,
                                           const juce::Slider::SliderStyle style,
                                           juce::Slider& slider)
{
    if (gainSliderThumbImage.isValid())
    {
        const int thumbWidth = gainSliderThumbImage.getWidth();
        const int thumbHeight = gainSliderThumbImage.getHeight();

        if (style == juce::Slider::LinearVertical)
        {
            const int halfThumbHeight = thumbHeight / 2;
            const double normalizedValue = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
            const double invertedNormalizedValue = 1.0 - normalizedValue;

            const int trackY = y + halfThumbHeight;
            const int trackHeight = height - thumbHeight;
            
            const int thumbCenterY = trackY + (int)(invertedNormalizedValue * trackHeight);
            
            const int thumbX = x + (width - thumbWidth) / 2;
            const int thumbY = thumbCenterY - halfThumbHeight;

            g.setImageResamplingQuality(Graphics::highResamplingQuality);
            g.drawImageAt(gainSliderThumbImage, thumbX, thumbY);
        }
        else // Horizontal
        {
            const int halfThumbWidth = thumbWidth / 2;
            const double normalizedValue = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());

            const int trackX = x + halfThumbWidth;
            const int trackWidth = width - thumbWidth;

            const int thumbCenterX = trackX + (int)(normalizedValue * trackWidth);
            
            const int thumbX = thumbCenterX - halfThumbWidth;
            const int thumbY = y + (height - thumbHeight) / 2;

            g.setImageResamplingQuality(Graphics::highResamplingQuality);
            g.drawImageAt(gainSliderThumbImage, thumbX, thumbY);
        }
    }
    else
    {
        juce::LookAndFeel_V4::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}