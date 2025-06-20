#pragma once

#include <JuceHeader.h>

#include "CustomKnobLNF.h"
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
    juce::Slider driveSlider, mixSlider, inputGainSlider, outputGainSlider;
    std::unique_ptr<CustomKnobLNF> customKnobLNF;
    juce::AudioProcessorValueTreeState::SliderAttachment driveAttachment, mixAttachment, inputGainAttachment, outputGainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SetekhAudioProcessorEditor)
};
