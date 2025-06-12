#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SetekhAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  SetekhAudioProcessorEditor(SetekhAudioProcessor&);
  ~SetekhAudioProcessorEditor() override = default;

  void paint(juce::Graphics&) override;
  void resized() override;

private:
    SetekhAudioProcessor& processor;

    juce::Slider amountSlider, mixSlider;
    juce::Label amountLabel, mixLabel;
    juce::AudioProcessorValueTreeState::SliderAttachment amountAttachment, mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SetekhAudioProcessorEditor)
};
