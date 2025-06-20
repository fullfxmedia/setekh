#include "PluginEditor.h"

SetekhAudioProcessorEditor::SetekhAudioProcessorEditor(SetekhAudioProcessor &p)
    : AudioProcessorEditor(&p), processor(p),
      driveAttachment(p.apvts, "drive", driveSlider),
      mixAttachment(p.apvts, "mix", mixSlider),
      inputGainAttachment(p.apvts, "inputGain", inputGainSlider) {
    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    customKnobLNF = std::make_unique<CustomKnobLNF>();
    driveSlider.setLookAndFeel(customKnobLNF.get());

    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);

    inputGainSlider.setSliderStyle(juce::Slider::LinearVertical);
    inputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);

    for (auto *comp: {&driveSlider, &mixSlider, &inputGainSlider}) {
        addAndMakeVisible(*comp);
    }

    setSize(475, 580);
}

void SetekhAudioProcessorEditor::paint(juce::Graphics &g) {
    // Background color
    g.fillAll(juce::Colours::black);

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
    int driveKnobSize = 225;
    int mixKnobSize = 80;

    int verticalSpacing = 30;
    int centerX = width / 2;

    // Drive knob at top center
    int driveY = 80;
    driveSlider.setBounds(centerX - driveKnobSize / 2, driveY, driveKnobSize, driveKnobSize);

    // Mix knob below the drive knob, centered horizontally
    int mixY = driveY + driveKnobSize + verticalSpacing;
    mixSlider.setBounds(centerX - mixKnobSize / 2, mixY, mixKnobSize, mixKnobSize);

    // Input Gain slider
    int inputGainSliderWidth = 50;
    int availableHeight = height - topBarHeight - 20;
    int inputGainSliderHeight = static_cast<int>(availableHeight * 0.8f);
    int inputGainSliderX = 20;
    int inputGainSliderY = topBarHeight + 10;
    inputGainSlider.setBounds(inputGainSliderX, inputGainSliderY, inputGainSliderWidth, inputGainSliderHeight);
}
