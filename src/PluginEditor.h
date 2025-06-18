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

    juce::Slider driveSlider, mixSlider;
    juce::AudioProcessorValueTreeState::SliderAttachment driveAttachment, mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SetekhAudioProcessorEditor)
};
