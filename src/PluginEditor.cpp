#include "PluginEditor.h"

SetekhAudioProcessorEditor::SetekhAudioProcessorEditor(SetekhAudioProcessor &p)
    : AudioProcessorEditor(&p), processor(p),
      driveAttachment(p.apvts, "drive", driveSlider),
      mixAttachment(p.apvts, "mix", mixSlider) {
    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);

    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);

    for (auto *comp: {&driveSlider, &mixSlider}) {
        addAndMakeVisible(*comp);
    }

    setSize(475, 580);
}

void SetekhAudioProcessorEditor::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::black);
}

void SetekhAudioProcessorEditor::resized() {
    // Large centered Amount knob
    int centerX = getWidth() / 2;
    int driveKnobSize = 150;
    driveSlider.setBounds(centerX - driveKnobSize / 2, 60, driveKnobSize, driveKnobSize);

    // Smaller Mix knob in bottom-right
    int mixKnobSize = 80;
    int padding = 20;
    mixSlider.setBounds(getWidth() - mixKnobSize - padding, getHeight() - mixKnobSize - 2 * padding, mixKnobSize,
                        mixKnobSize);
}
