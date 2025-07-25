#include "PluginEditor.h"

SetekhAudioProcessorEditor::SetekhAudioProcessorEditor(SetekhAudioProcessor &p)
    : AudioProcessorEditor(&p), processor(p),
      driveAttachment(p.apvts, "drive", driveSlider),
      mixAttachment(p.apvts, "mix", mixSlider),
      inputGainAttachment(p.apvts, "inputGain", inputGainSlider),
      outputGainAttachment(p.apvts, "outputGain", outputGainSlider) {

    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    customKnobLNF = std::make_unique<CustomKnobLNF>();
    driveSlider.setLookAndFeel(customKnobLNF.get());

    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);

    // Set up input gain slider
    inputGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    inputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    inputGainSlider.setRange(-60.0, 12.0, 0.1);
    inputGainSlider.setValue(0.0);

    // Configure and apply input gain look and feel
    inputGainLNF.setSliderType(CustomSliderLNF::InputGain);
    inputGainSlider.setLookAndFeel(&inputGainLNF);
    addAndMakeVisible(inputGainSlider);

    // Set up output gain slider
    outputGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    outputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    outputGainSlider.setRange(-60.0, 12.0, 0.1);
    outputGainSlider.setValue(0.0);

    // Configure and apply output gain look and feel
    outputGainLNF.setSliderType(CustomSliderLNF::OutputGain);
    outputGainSlider.setLookAndFeel(&outputGainLNF);
    addAndMakeVisible(outputGainSlider);

    // Bypass toggle
    bypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(p.apvts, "bypass", bypassToggle);
    bypassToggle.setButtonText("Bypass");
    bypassToggle.setColour(juce::ToggleButton::textColourId, juce::Colours::white);

    // Show all sliders
    for (auto *comp: {&driveSlider, &mixSlider, &inputGainSlider, &outputGainSlider}) {
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
    int mixKnobSize = 80;

    int verticalSpacing = 30;
    int centerX = width / 2;

    // Drive knob at top center
    int driveY = 75;
    driveSlider.setBounds(centerX - driveKnobSize / 2, driveY, driveKnobSize, driveKnobSize);

    // Mix knob below the drive knob, centered horizontally
    int mixY = driveY + driveKnobSize + verticalSpacing;
    mixSlider.setBounds(centerX - mixKnobSize / 2, mixY, mixKnobSize, mixKnobSize);

    // Gain sliders
    int sliderWidth = 50;
    int sliderY = topBarHeight + 10;

    // Input Gain slider
    int availableHeight = height - topBarHeight - 20;
    int inputGainSliderHeight = static_cast<int>(availableHeight * 0.8f);
    int inputGainSliderX = 40;
    int inputGainSliderY = sliderY;
    inputGainSlider.setBounds(inputGainSliderX, inputGainSliderY, sliderWidth, inputGainSliderHeight);

    int outputGainSliderHeight = static_cast<int>(availableHeight * 0.8f);
    int outputGainSliderX = width - sliderWidth - 40;
    outputGainSlider.setBounds(outputGainSliderX, sliderY, sliderWidth, outputGainSliderHeight);

    int bypassWidth = 80;
    int bypassHeight = 30;
    int bypassX = width - bypassWidth - 15; // 15px margin from right edge
    int bypassY = (topBarHeight - bypassHeight) / 2; // Center vertically in top bar
    bypassToggle.setBounds(bypassX, bypassY, bypassWidth, bypassHeight);
}
