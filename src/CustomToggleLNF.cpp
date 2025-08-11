//
// Copyright (c) 2025 Full FX Media
//

#include "CustomToggleLNF.h"

CustomToggleLNF::CustomToggleLNF()
{
    toggleOn  = juce::ImageCache::getFromMemory (BinaryData::toggle_on_png,
                                                 BinaryData::toggle_on_pngSize);
    toggleOff = juce::ImageCache::getFromMemory (BinaryData::toggle_off_png,
                                                 BinaryData::toggle_off_pngSize);
}

void CustomToggleLNF::drawToggleButton (juce::Graphics& g,
                                        juce::ToggleButton& button,
                                        bool shouldDrawButtonAsHighlighted,
                                        bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds().toFloat();
    auto imageArea = bounds.reduced(2.0f);

    // Draw your custom toggle image
    if (button.getToggleState())
    {
        g.drawImage (toggleOn, imageArea, juce::RectanglePlacement::centred);
    }
    else
    {
        g.drawImage (toggleOff, imageArea, juce::RectanglePlacement::centred);
    }

    // If you want to draw the text as well, uncomment this:
    if (button.getButtonText().isNotEmpty())
    {
        g.setColour (button.findColour (juce::ToggleButton::textColourId));
        g.setFont (14.0f);

        auto textArea = bounds.reduced (4.0f);
        g.drawFittedText (button.getButtonText(), textArea.toNearestInt(),
                         juce::Justification::centred, 1);
    }
}