#include "PluginEditor.h"

SetekhAudioProcessorEditor::SetekhAudioProcessorEditor(SetekhAudioProcessor &p)
    : AudioProcessorEditor(&p),
      driveAttachment(p.apvts, "drive", driveSlider),
      inputGainAttachment(p.apvts, "inputGain", inputGainSlider),
      outputGainAttachment(p.apvts, "outputGain", outputGainSlider) {

    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 30);
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

    // Set up input gain slider
    inputGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    inputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    inputGainSlider.setRange(-24.0, 24.0, 0.1);
    inputGainSlider.setValue(0.0);
    inputGainLNF.setSliderType(CustomSliderLNF::SliderType::InputGain);
    inputGainSlider.setLookAndFeel(&inputGainLNF);
    addAndMakeVisible(inputGainSlider);

    // Set up output gain slider
    outputGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    outputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    outputGainSlider.setRange(-24.0, 24.0, 0.1);
    outputGainSlider.setValue(0.0);
    outputGainLNF.setSliderType(CustomSliderLNF::SliderType::OutputGain);
    outputGainSlider.setLookAndFeel(&outputGainLNF);
    addAndMakeVisible(outputGainSlider);

    // Link Gains toggle
    linkGainsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(p.apvts, "linkGains", linkGainsToggle);
    linkGainsToggle.setButtonText("Link Gains");
    linkGainsToggle.setColour(juce::ToggleButton::textColourId, juce::Colours::white);
    addAndMakeVisible(linkGainsToggle);

    // Bypass toggle
    bypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(p.apvts, "bypass", bypassToggle);
    bypassToggle.setButtonText("Bypass");
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

    setSize(475, 580);
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
    g.setFont(juce::Font("Arial", 24.0f, juce::Font::bold));
    g.drawText("SETEKH", 15, 10, 200, 30, juce::Justification::left);
}

void SetekhAudioProcessorEditor::resized() {
    int width = getWidth();

    // Knob sizes
    int driveKnobSize = 250;

    int centerX = width / 2;

    // Drive knob at top center
    int driveY = 75;
    driveSlider.setBounds(centerX - driveKnobSize / 2, driveY, driveKnobSize, driveKnobSize);

    // Link Gains toggle below drive knob
    int linkGainsToggleWidth = 100;
    int linkGainsToggleHeight = 30;
    linkGainsToggle.setBounds(centerX - linkGainsToggleWidth / 2, driveY + driveKnobSize + 10, linkGainsToggleWidth, linkGainsToggleHeight);

    int sliderWidth = 80;
    int sliderHeight = 420;
    int sliderY = topBarHeight + 20;
    int inputGainSliderX = 30;
    int outputGainSliderX = width - sliderWidth - 30;

    inputGainSlider.setBounds(inputGainSliderX, sliderY, sliderWidth, sliderHeight);
    outputGainSlider.setBounds(outputGainSliderX, sliderY, sliderWidth, sliderHeight);

    // Bypass toggle (unchanged)
    int bypassWidth = 80;
    int bypassHeight = 30;
    int bypassX = width - bypassWidth - 15;
    int bypassY = (topBarHeight - bypassHeight) / 2;
    bypassToggle.setBounds(bypassX, bypassY, bypassWidth, bypassHeight);
}