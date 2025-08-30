//
// Copyright (c) 2025 Full FX Media
//

#include "CustomSplashScreen.h"

CustomSplashScreen::CustomSplashScreen()
{
    // Start hidden, and capture mouse clicks so it dismisses properly
    setVisible(false);
    setInterceptsMouseClicks(true, true);
}

void CustomSplashScreen::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff3B3A45));
    g.setColour(juce::Colours::white);
    g.setFont(48.0f);
    g.drawText("SETEKH22", getLocalBounds(), juce::Justification::centred, true);
}

void CustomSplashScreen::mouseUp(const juce::MouseEvent&)
{
    setVisible(false);
}
