//
// Copyright (c) 2025 Full FX Media
//

#pragma once

#include <JuceHeader.h>

class CustomSplashScreen : public juce::Component
{
public:
    CustomSplashScreen();

    void paint(juce::Graphics& g) override;
    void mouseUp(const juce::MouseEvent& event) override;
};




