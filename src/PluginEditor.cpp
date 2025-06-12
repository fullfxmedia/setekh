#include "PluginEditor.h"

SetekhAudioProcessorEditor::SetekhAudioProcessorEditor(SetekhAudioProcessor& p)
  : AudioProcessorEditor(&p), processor(p),
    amountAttachment(p.apvts, "amount", amountSlider),
    mixAttachment(p.apvts, "mix", mixSlider) {
    
  amountLabel.setText("Amount", juce::dontSendNotification);
  mixLabel.setText("Mix", juce::dontSendNotification);
  
  for (auto* comp : { &amountSlider, &mixSlider }) {
      addAndMakeVisible(*comp);
      comp->setSliderStyle(juce::Slider::Rotary);
      comp->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
  }

  for (auto* label : { &amountLabel, &mixLabel }) {
      addAndMakeVisible(*label);
  }

  setSize(300, 200);
}

void SetekhAudioProcessorEditor::paint(juce::Graphics& g) {
  g.fillAll(juce::Colours::black);
}

void SetekhAudioProcessorEditor::resized() {
  amountSlider.setBounds(40, 40, 100, 100);
  amountLabel.setBounds(40, 20, 100, 20);

  mixSlider.setBounds(160, 40, 100, 100);
  mixLabel.setBounds(160, 20, 100, 20);
}
