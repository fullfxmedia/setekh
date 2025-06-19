//
// Copyright (c) 2025 Full FX Media
//

#include "PluginProcessor.h"
#include "PluginEditor.h"

SetekhAudioProcessor::SetekhAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
          .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "PARAMS", createParams()) {
}

AudioProcessorValueTreeState::ParameterLayout SetekhAudioProcessor::createParams() {
    std::vector<std::unique_ptr<RangedAudioParameter> > params;
    params.push_back(std::make_unique<AudioParameterFloat>("drive", "Drive", 0.0f, 10.0f, 1.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("mix", "Mix", 0.0f, 1.0f, 0.5f));
    return {params.begin(), params.end()};
}

SetekhAudioProcessor::~SetekhAudioProcessor() = default;

void SetekhAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
}

void SetekhAudioProcessor::releaseResources() {
}

bool SetekhAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}

void SetekhAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &) {
    auto drive = apvts.getRawParameterValue("drive")->load();
    auto mix = apvts.getRawParameterValue("mix")->load();

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
        auto *samples = buffer.getWritePointer(ch);
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            auto clean = samples[i];

            // Soft clip using atan
            float clipped = std::atan(drive * clean);
            clipped /= std::atan(drive);

            // Mix dry and wet
            samples[i] = clean * (1.0f - mix) + clipped * mix;
        }
    }
}

juce::AudioProcessorEditor *SetekhAudioProcessor::createEditor() {
    return new SetekhAudioProcessorEditor(*this);
}

bool SetekhAudioProcessor::hasEditor() const { return true; }

const juce::String SetekhAudioProcessor::getName() const { return "Setekh"; }

bool SetekhAudioProcessor::acceptsMidi() const { return false; }
bool SetekhAudioProcessor::producesMidi() const { return false; }
bool SetekhAudioProcessor::isMidiEffect() const { return false; }
double SetekhAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int SetekhAudioProcessor::getNumPrograms() { return 1; }
int SetekhAudioProcessor::getCurrentProgram() { return 0; }

void SetekhAudioProcessor::setCurrentProgram(int) {
}

const juce::String SetekhAudioProcessor::getProgramName(int) { return {}; }

void SetekhAudioProcessor::changeProgramName(int, const juce::String &) {
}

void SetekhAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
    // Save plugin state here
    juce::MemoryOutputStream stream(destData, true);
    // stream.writeFloat(someValue);
}

void SetekhAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    // Restore plugin state here
    juce::MemoryInputStream stream(data, static_cast<size_t>(sizeInBytes), false);
    // someValue = stream.readFloat();
}

// Required factory function
juce::AudioProcessor * JUCE_CALLTYPE createPluginFilter() {
    return new SetekhAudioProcessor();
}
