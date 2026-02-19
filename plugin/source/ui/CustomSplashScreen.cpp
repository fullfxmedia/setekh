//
// Copyright (c) 2025 Full FX Media
//

#include "Setekh/ui/CustomSplashScreen.h"

CustomSplashScreen::CustomSplashScreen(const juce::String& versionString,
                                       const juce::String& buildArch)
    :   setekhLink("https://www.github.com/fullfxmedia/setekh", juce::URL("https://www.github.com/fullfxmedia/setekh")),
        urlLink("https://www.fullfxmedia.com", juce::URL("https://www.fullfxmedia.com"))
{
    setOpaque(true);
    addAndMakeVisible(logoLabel);
    addAndMakeVisible(versionLabel);
    addAndMakeVisible(createdByLabel);
    addAndMakeVisible(setekhLink);
    addAndMakeVisible(urlLink);

    // Version + build label
    versionLabel.setText("Version " + versionString + " (" + buildArch + ")", juce::dontSendNotification);
    versionLabel.setJustificationType(juce::Justification::centred);
    versionLabel.setFont(juce::Font(18.0f));
    versionLabel.setColour(juce::Label::textColourId, juce::Colours::white);

    // Logo label styling
    logoLabel.setText("SETEKH", juce::dontSendNotification);
    logoLabel.setJustificationType(juce::Justification::centredTop);
    logoLabel.setFont(juce::Font(48.0f, juce::Font::bold));
    logoLabel.setColour(juce::Label::textColourId, juce::Colours::white);

    // Created by label styling
    createdByLabel.setText("Created by Full FX Media LLC for creators", juce::dontSendNotification);
    createdByLabel.setJustificationType(juce::Justification::centredTop);
    createdByLabel.setFont(juce::Font(14.0f));
    createdByLabel.setColour(juce::Label::textColourId, juce::Colours::white);

    auto bottomArea = getLocalBounds().reduced(20);

    // Github project link
    auto setekhLinkArea = bottomArea.removeFromTop(20);
    setekhLink.setFont(juce::Font(16.0f), false, juce::Justification::centred);
    setekhLink.setColour(juce::HyperlinkButton::textColourId, juce::Colours::lightblue);
    setekhLink.setBounds(setekhLinkArea.withSizeKeepingCentre(setekhLink.getWidth(), setekhLink.getHeight()));

    // URL hyperlink styling
    auto linkArea = bottomArea.removeFromTop(30);
    urlLink.setFont(juce::Font(16.0f), false, juce::Justification::centred);
    urlLink.setColour(juce::HyperlinkButton::textColourId, juce::Colours::lightblue);
    urlLink.setBounds(linkArea.withSizeKeepingCentre(linkArea.getWidth(), linkArea.getHeight()));
}

void CustomSplashScreen::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(20, 20, 20));

    // draw bounds around the hyperlink for debugging
    g.drawRect(urlLink.getBounds(), 1);

    g.drawRect(logoLabel.getBounds(), 1);
}

void CustomSplashScreen::resized()
{
    auto area = getLocalBounds();
    int width = area.getWidth();
    int height = area.getHeight();

    // Position logo at top center
    auto logoFont = logoLabel.getFont();
    auto logoText = logoLabel.getText();
    int logoW = static_cast<int>(logoFont.getStringWidth(logoText));
    int logoH = static_cast<int>(logoFont.getHeight());
    int centerX = area.getWidth() / 2;
    logoLabel.setBounds(centerX - logoW / 2, 100, logoW, logoH);

    // Version + build info
    versionLabel.setBounds(0, height / 2 - 10, width, 20);

    const int bottomMargin = 20;
    const int lineHeight = 20;

    urlLink.setBounds(10, getHeight() - bottomMargin - lineHeight, getWidth() - 20, lineHeight);
    setekhLink.setBounds(10, getHeight() - bottomMargin - 2 * lineHeight, getWidth() - 20, lineHeight);
    createdByLabel.setBounds(10, getHeight() - bottomMargin - 3 * lineHeight, getWidth() - 20, lineHeight);
    
    // // Created by label at bottom center
    // createdByLabel.setBounds(0, area.getHeight() - 30 - 50, width, 30);
    //
    // // Setekh project link
    // setekhLink.setBounds(0, height - 50, width, 20);
    //
    // // URL link at very bottom
    // urlLink.setBounds(0, height - 25, width, 20);
}

void CustomSplashScreen::mouseUp(const juce::MouseEvent& event)
{
    if (!urlLink.getBounds().contains(event.getPosition()))
    {
        setVisible(false);
    }
}
