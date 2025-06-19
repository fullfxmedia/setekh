#include "PluginEditor.h"

SetekhAudioProcessorEditor::SetekhAudioProcessorEditor(SetekhAudioProcessor &p)
    : AudioProcessorEditor(&p), processor(p),
      driveAttachment(p.apvts, "drive", driveSlider),
      mixAttachment(p.apvts, "mix", mixSlider) {
    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);

    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);

    customKnobLNF = std::make_unique<CustomKnobLNF>();
    driveSlider.setLookAndFeel(customKnobLNF.get());


    for (auto *comp: {&driveSlider, &mixSlider}) {
        addAndMakeVisible(*comp);
    }

    setSize(475, 580);
}

void SetekhAudioProcessorEditor::paint(juce::Graphics &g) {
    // Background color
    g.fillAll(juce::Colours::black);

    // Top gray bar
    int topBarHeight = 50;
    g.setColour(juce::Colour(0xff2e2e2e));
    g.fillRect(0, 0, getWidth(), topBarHeight);

    // "SETEKH" label
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font("Helvetica", 24.0f, juce::Font::bold));
    g.drawText("SETEKH", 15, 10, 200, 30, juce::Justification::left);
}

void SetekhAudioProcessorEditor::resized() {
    int width = getWidth();

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
}
