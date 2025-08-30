//
// Copyright (c) 2025 Full FX Media
//

#include "CustomSplashScreen.h"

CustomSplashScreen::CustomSplashScreen()
    : urlLink("https://www.fullfxmedia.com", juce::URL("https://www.fullfxmedia.com"))
{
    setOpaque(true);
    addAndMakeVisible(logoLabel);
    addAndMakeVisible(createdByLabel);
    addAndMakeVisible(urlLink);

    // Logo label styling
    logoLabel.setText("SETEKH", juce::dontSendNotification);
    logoLabel.setJustificationType(juce::Justification::centredTop);
    logoLabel.setFont(juce::Font(48.0f, juce::Font::bold));
    logoLabel.setColour(juce::Label::textColourId, juce::Colours::white);

    // Created by label styling
    createdByLabel.setText("Created by Full FX Media for creators", juce::dontSendNotification);
    createdByLabel.setJustificationType(juce::Justification::centredTop);
    createdByLabel.setFont(juce::Font(14.0f));
    createdByLabel.setColour(juce::Label::textColourId, juce::Colours::white);

    // URL hyperlink styling
    auto area = getLocalBounds().reduced(20);
    auto linkArea = area.removeFromTop(30);
    urlLink.setColour(juce::HyperlinkButton::textColourId, juce::Colours::lightblue);
    urlLink.setBounds(linkArea.withSizeKeepingCentre(linkArea.getWidth(), linkArea.getHeight()));
}

void CustomSplashScreen::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(20, 20, 20));

    // draw bounds around the hyperlink for debugging
    g.setColour(juce::Colours::red);
    g.drawRect(urlLink.getBounds(), 1);

    g.setColour(juce::Colours::red);
    g.drawRect(logoLabel.getBounds(), 1);
}

void CustomSplashScreen::resized()
{
    auto area = getLocalBounds();
    int width = area.getWidth();

    // Position logo at top center
    auto logoFont = logoLabel.getFont();
    auto logoText = logoLabel.getText();
    int logoW = static_cast<int>(logoFont.getStringWidth(logoText));
    int logoH = static_cast<int>(logoFont.getHeight());
    int centerX = area.getWidth() / 2;
    logoLabel.setBounds(centerX - logoW / 2, 20, logoW, logoH);

    // Created by label at bottom center
    createdByLabel.setBounds(0, area.getHeight() - 30 - 50, width, 30);

    // Position URL just under logo
    urlLink.setBounds(0, area.getHeight() - 30 - 20, width, 30);
}

void CustomSplashScreen::mouseUp(const juce::MouseEvent& event)
{
    if (!urlLink.getBounds().contains(event.getPosition()))
    {
        setVisible(false);
    }
}
