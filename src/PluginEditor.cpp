#include "PluginEditor.h"

SetekhAudioProcessorEditor::SetekhAudioProcessorEditor(SetekhAudioProcessor &p)
    : AudioProcessorEditor(&p), processor(p),
      driveAttachment(p.apvts, "drive", driveSlider),
      inputGainAttachment(p.apvts, "inputGain", inputGainSlider),
      outputGainAttachment(p.apvts, "outputGain", outputGainSlider) {

    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    customKnobLNF = std::make_unique<CustomKnobLNF>();
    driveSlider.setLookAndFeel(customKnobLNF.get());

    // Set up input gain slider
    inputGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    inputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    inputGainSlider.setRange(-24.0, 24.0, 0.1);
    inputGainSlider.setNumDecimalPlacesToDisplay(0.01f);
    inputGainSlider.setValue(0.0);
    inputGainLNF.setSliderType(CustomSliderLNF::SliderType::InputGain);
    inputGainSlider.setLookAndFeel(&inputGainLNF);
    addAndMakeVisible(inputGainSlider);

    // Set up output gain slider
    outputGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    outputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    outputGainSlider.setRange(-24.0, 24.0, 0.1);
    outputGainSlider.setNumDecimalPlacesToDisplay(0.01f);
    outputGainSlider.setValue(0.0);
    outputGainLNF.setSliderType(CustomSliderLNF::SliderType::OutputGain);
    outputGainSlider.setLookAndFeel(&outputGainLNF);
    addAndMakeVisible(outputGainSlider);

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

    setSize(475, 580);
}

void SetekhAudioProcessorEditor::paint(juce::Graphics &g) {
    // Background color
    g.fillAll(juce::Colour::fromRGB(0x3B, 0x3A, 0x45));

    // Top gray bar
    g.setColour(juce::Colour(0xff2e2e2e));
    g.fillRect(0, 0, getWidth(), topBarHeight);

    // "SETEKH" label
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font("Helvetica", 24.0f, juce::Font::bold));
    g.drawText("SETEKH", 15, 10, 200, 30, juce::Justification::left);
}

void SetekhAudioProcessorEditor::resized() {
    int width = getWidth();
    int height = getHeight();

    // Knob sizes
    int driveKnobSize = 250;

    int centerX = width / 2;

    // Drive knob at top center
    int driveY = 75;
    driveSlider.setBounds(centerX - driveKnobSize / 2, driveY, driveKnobSize, driveKnobSize);

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