#include "PluginEditor.h"

SetekhAudioProcessorEditor::SetekhAudioProcessorEditor(SetekhAudioProcessor &p)
    : AudioProcessorEditor(&p),
      driveAttachment(p.apvts, "drive", driveSlider),
      inputGainAttachment(p.apvts, "inputGain", inputGainSlider),
      outputGainAttachment(p.apvts, "outputGain", outputGainSlider) {

    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    driveSlider.setRange(0.0, 5.0, 0.01);
    driveSlider.setNumDecimalPlacesToDisplay(0);
    customKnobLNF = std::make_unique<CustomKnobLNF>();
    driveSlider.setLookAndFeel(customKnobLNF.get());

    // Display a range of 0-100 from the drives underlying value of 0-5
    driveSlider.textFromValueFunction = [](double value) {
        int displayValue = static_cast<int>(std::round((value / 5.0) * 100.0));
        return juce::String(displayValue);
    };
    driveSlider.valueFromTextFunction = [](const juce::String& text) {
        double displayValue = text.getDoubleValue();
        return (displayValue / 100.0) * 5.0;
    };
    driveSlider.updateText();

    // Input gain slider
    inputGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    inputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    inputGainSlider.setRange(-24.0, 24.0, 0.1);
    inputGainSlider.setValue(0.0);
    inputGainLNF.setSliderType(CustomSliderLNF::SliderType::InputGain);
    inputGainSlider.setLookAndFeel(&inputGainLNF);
    addAndMakeVisible(inputGainSlider);

    // Output gain slider
    outputGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    outputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    outputGainSlider.setRange(-24.0, 24.0, 0.1);
    outputGainSlider.setValue(0.0);
    outputGainLNF.setSliderType(CustomSliderLNF::SliderType::OutputGain);
    outputGainSlider.setLookAndFeel(&outputGainLNF);
    addAndMakeVisible(outputGainSlider);

    auto roboto = juce::Typeface::createSystemTypefaceFor(
        BinaryData::RobotoRegular_ttf,
        BinaryData::RobotoRegular_ttfSize
    );

    auto robotoBold = juce::Typeface::createSystemTypefaceFor(
        BinaryData::RobotoBold_ttf,
        BinaryData::RobotoBold_ttfSize
    );

    // Link Gains label & toggle
    linkLabel.setText("LINK", juce::dontSendNotification);
    linkLabel.setFont(juce::Font(robotoBold).withHeight(20.0f).withStyle(juce::Font::plain));
    linkLabel.setJustificationType(juce::Justification::centred);
    linkLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    linkLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(linkLabel);

    linkGainsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(p.apvts, "linkGains", linkGainsToggle);
    linkGainsToggle.setButtonText(juce::String());
    linkGainsToggleLNF = std::make_unique<CustomToggleLNF>();
    linkGainsToggle.setLookAndFeel(linkGainsToggleLNF.get());
    linkGainsToggle.setColour(juce::ToggleButton::textColourId, juce::Colours::white);
    addAndMakeVisible(linkGainsToggle);

    // Bypass label & toggle
    bypassLabel.setText("BYPASS", juce::dontSendNotification);
    bypassLabel.setFont(juce::Font(roboto).withHeight(20.0f).withStyle(juce::Font::plain));
    bypassLabel.setJustificationType(juce::Justification::centred);
    bypassLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    bypassLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    bypassLabel.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(bypassLabel);

    bypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(p.apvts, "bypass", bypassToggle);
    bypassToggleLNF = std::make_unique<CustomToggleLNF>();
    bypassToggle.setLookAndFeel(bypassToggleLNF.get());
    bypassToggle.setColour(juce::ToggleButton::textColourId, juce::Colours::white);

    // Show all sliders
    for (auto *comp: {&driveSlider, &inputGainSlider, &outputGainSlider}) {
        addAndMakeVisible(*comp);
    }

    // Show bypass toggle
    addAndMakeVisible(bypassToggle);

    // Add key listener to reset slider on backspace
    inputGainSlider.addKeyListener(this);
    outputGainSlider.addKeyListener(this);

    // Adjusts the input/output gains if "Link Gains" is checked
    inputGainSlider.onValueChange = [this] {
        if (linkGainsToggle.getToggleState()) {
            outputGainSlider.setValue(-inputGainSlider.getValue());
        }
    };

    outputGainSlider.onValueChange = [this] {
        if (linkGainsToggle.getToggleState()) {
            inputGainSlider.setValue(-outputGainSlider.getValue());
        }
    };

    linkGainsToggle.onStateChange = [this] {
        if (linkGainsToggle.getToggleState()) {
            outputGainSlider.setValue(-inputGainSlider.getValue());
        }
    };

    setSize(475, 525);
}

bool SetekhAudioProcessorEditor::keyPressed(const juce::KeyPress &key, juce::Component *originatingComponent)
{
    if (key.getKeyCode() == juce::KeyPress::backspaceKey)
    {
        if (originatingComponent == &inputGainSlider)
        {
            inputGainSlider.setValue(0.0);
            return true;
        } else if (originatingComponent == &outputGainSlider) {
            outputGainSlider.setValue(0.0);
        }
    }
    return false;
}

void SetekhAudioProcessorEditor::paint(juce::Graphics &g) {
    // Background color
    g.fillAll(juce::Colour::fromRGB(0x3B, 0x3A, 0x45));

    // Top gray bar
    g.setColour(juce::Colour(0xff2e2e2e));
    g.fillRect(0, 0, getWidth(), topBarHeight);

    // "SETEKH" label
    g.setColour(juce::Colours::white);
    auto bungeeTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::BungeeRegular_ttf, BinaryData::BungeeRegular_ttfSize);
    juce::Font bungeeFont(bungeeTypeface);
    bungeeFont.setHeight(36.0f);
    g.setFont(bungeeFont);
    g.drawText("SETEKH", 15, 10, 200, 30, juce::Justification::left);
}

void SetekhAudioProcessorEditor::resized() {
    int width = getWidth();
    int centerX = width / 2;

    // Knob sizes, Drive knob at top center
    int driveWidth = 250;
    int driveHeight = 250;
    int drivePosY = 75;
    driveSlider.setBounds(centerX - driveWidth / 2, drivePosY, driveWidth, driveHeight);

    // Input and Output gain sliders
    int sliderWidth = 120;
    int sliderHeight = 420;
    int sliderY = topBarHeight + 20;
    int inputGainSliderX = 10;
    int outputGainSliderX = width - sliderWidth - 10;
    inputGainSlider.setBounds(inputGainSliderX, sliderY, sliderWidth, sliderHeight);
    outputGainSlider.setBounds(outputGainSliderX, sliderY, sliderWidth, sliderHeight);

    // Link/Bypass Toggle common
    int toggleWidth = 159;
    int toggleHeight = 59;
    int labelWidth = 100;
    int labelHeight = 28;

    // Link toggle, directly below drive knob
    int groupWidth = 100;
    int groupX = centerX - groupWidth / 2;
    int groupY = drivePosY + driveWidth + 40;
    linkLabel.setBounds(groupX, groupY, labelWidth, labelHeight);
    linkGainsToggle.setBounds(centerX - toggleWidth / 2, groupY + 20, toggleWidth, toggleHeight);

    // Bypass toggle
    int bypassX = width - toggleWidth - 35;
    int bypassY = (topBarHeight - toggleHeight) / 2;
    bypassLabel.setBounds(bypassX + 95, bypassY + 15, labelWidth, labelHeight);
    bypassToggle.setBounds(bypassX, bypassY, toggleWidth, toggleHeight);
}