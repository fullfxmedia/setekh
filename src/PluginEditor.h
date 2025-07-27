#pragma once

#include <JuceHeader.h>

#include "CustomKnobLNF.h"
#include "CustomSliderLNF.h"
#include "PluginProcessor.h"

class SetekhAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    SetekhAudioProcessorEditor(SetekhAudioProcessor &);

    ~SetekhAudioProcessorEditor() override = default;

    void paint(juce::Graphics &) override;

    void resized() override;

private:
    SetekhAudioProcessor &processor;

    int topBarHeight = 50;
    juce::Slider driveSlider, inputGainSlider, outputGainSlider;

    juce::ToggleButton bypassToggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    // Look and Feel objects
    std::unique_ptr<CustomKnobLNF> customKnobLNF;
    CustomSliderLNF inputGainLNF;
    CustomSliderLNF outputGainLNF;

    juce::AudioProcessorValueTreeState::SliderAttachment driveAttachment, inputGainAttachment, outputGainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SetekhAudioProcessorEditor)
};
