//
// Copyright (c) 2025 Full FX Media
//

#pragma once

#include <JuceHeader.h>

class CustomSplashScreen : public juce::Component
{
public:
    CustomSplashScreen(const juce::String& versionString, const juce::String& buildArch);

    void paint(juce::Graphics& g) override;
    void mouseUp(const juce::MouseEvent& event) override;
    void resized() override;

private:
    juce::Label logoLabel;
    juce::Label versionLabel;
    juce::Label createdByLabel;
    juce::HyperlinkButton setekhLink;
    juce::HyperlinkButton urlLink;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomSplashScreen)
};




