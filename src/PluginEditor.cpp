#include "PluginEditor.h"

SetekhAudioProcessorEditor::SetekhAudioProcessorEditor(SetekhAudioProcessor& p)
  : AudioProcessorEditor(&p), processor(p),
    amountAttachment(p.apvts, "amount", amountSlider),
    mixAttachment(p.apvts, "mix", mixSlider) {

  amountSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
  amountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);

  mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
  mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);
  
  for (auto* comp : { &amountSlider, &mixSlider }) {
      addAndMakeVisible(*comp);
  }

  setSize(250, 400);
}

void SetekhAudioProcessorEditor::paint(juce::Graphics& g) {
  g.fillAll(juce::Colours::black);
}

void SetekhAudioProcessorEditor::resized()
{
    // Large centered Amount knob
    int centerX = getWidth() / 2;
    int amountKnobSize = 150;
    amountSlider.setBounds(centerX - amountKnobSize / 2, 60, amountKnobSize, amountKnobSize);

    // Smaller Mix knob in bottom-right
    int mixKnobSize = 80;
    int padding = 20;
    mixSlider.setBounds(getWidth() - mixKnobSize - padding, getHeight() - mixKnobSize - 2 * padding, mixKnobSize, mixKnobSize);
}