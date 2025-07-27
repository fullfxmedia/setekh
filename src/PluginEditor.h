#pragma once

#include <JuceHeader.h>

#include "CustomKnobLNF.h"
#include "CustomSliderLNF.h"
#include "PluginProcessor.h"

class SetekhAudioProcessorEditor : public juce::AudioProcessorEditor, public juce::KeyListener {
public:
    SetekhAudioProcessorEditor(SetekhAudioProcessor &);

    ~SetekhAudioProcessorEditor() override = default;

    using juce::Component::keyPressed;

    void paint(juce::Graphics &) override;

    void resized() override;

    bool keyPressed(const juce::KeyPress &key, juce::Component *originatingComponent) override;

private:
    int topBarHeight = 50;
    juce::Slider driveSlider, inputGainSlider, outputGainSlider;

    juce::ToggleButton bypassToggle, linkGainsToggle;
    juce::Label linkLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment, linkGainsAttachment;

    // Look and Feel objects
    std::unique_ptr<CustomKnobLNF> customKnobLNF;
    CustomSliderLNF inputGainLNF;
    CustomSliderLNF outputGainLNF;

    juce::AudioProcessorValueTreeState::SliderAttachment driveAttachment, inputGainAttachment, outputGainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SetekhAudioProcessorEditor)
};
