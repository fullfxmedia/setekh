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
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    // Drive knob
    params.push_back(std::make_unique<AudioParameterFloat>("drive", "Drive", 0.0f, 5.0f, 0));

    // input/output gain parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>("inputGain", "Input Gain",juce::NormalisableRange<float>(-24.0f, 24.0f), 0.0f,
    juce::AudioParameterFloatAttributes().withStringFromValueFunction([](float value, int) {
        return juce::String(value, 1);
    })));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("outputGain", "Output Gain", juce::NormalisableRange<float>(-24.0f, 24.0f), 0.0f,
    juce::AudioParameterFloatAttributes().withStringFromValueFunction([](float value, int) {
        return juce::String(value, 1);
    })));

    // Bypass toggle
    params.push_back(std::make_unique<juce::AudioParameterBool>("bypass", "Bypass", false));

    // Link Gains toggle
    params.push_back(std::make_unique<juce::AudioParameterBool>("linkGains", "Link Gains", false));

    return {params.begin(), params.end()};
}

SetekhAudioProcessor::~SetekhAudioProcessor() = default;

void SetekhAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    spec.sampleRate = static_cast<uint32>(sampleRate);
    spec.maximumBlockSize = static_cast<uint32>(samplesPerBlock);
    spec.numChannels = static_cast<uint32>(getTotalNumOutputChannels());

    highShelfBoost.reset();
    highShelfCut.reset();

    highShelfBoost.prepare(spec);
    highShelfCut.prepare(spec);

    float cutoffFreq = 7500.0f;
    float qValue = 0.707f;
    float gainBoost = juce::Decibels::decibelsToGain(6.0f);
    float gainCut = juce::Decibels::decibelsToGain(-6.0f);

    auto coeffBoost = juce::dsp::IIR::Coefficients<float>::makeHighShelf(
        sampleRate, cutoffFreq, qValue, gainBoost);
    auto coeffCut = juce::dsp::IIR::Coefficients<float>::makeHighShelf(
        sampleRate, cutoffFreq, qValue, gainCut);

    highShelfBoost.coefficients = coeffBoost;
    highShelfCut.coefficients = coeffCut;
}

void SetekhAudioProcessor::releaseResources() {
}

bool SetekhAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}

void SetekhAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &) {
    // If bypass is enabled, do nothing
    auto bypass = apvts.getRawParameterValue("bypass")->load();
    if (bypass > 0.5f) {
        return;
    }

    // High shelf boost
    juce::dsp::AudioBlock<float> block(buffer);
    highShelfBoost.process(juce::dsp::ProcessContextReplacing(block));

    auto drive = apvts.getRawParameterValue("drive")->load();
    auto inputGain = juce::Decibels::decibelsToGain(apvts.getRawParameterValue("inputGain")->load());
    auto outputGain = juce::Decibels::decibelsToGain(apvts.getRawParameterValue("outputGain")->load());

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
        auto *samples = buffer.getWritePointer(ch);
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            // Apply input gain
            auto clean = samples[i] * inputGain;

            // Apply drive-based distortion directly
            float driveAmount = drive / 5.0f;
            float distorted = std::tanh(clean * 5.0f * 0.7f);
            float wet = (1.0f - driveAmount) * clean + driveAmount * distorted;

            // Apply output gain
            samples[i] = wet * outputGain;
        }
    }

    // // High shelf cut
    highShelfCut.process(juce::dsp::ProcessContextReplacing(block));
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
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void SetekhAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr && xmlState->hasTagName (apvts.state.getType())) {
        apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
}

// Required factory function
juce::AudioProcessor * JUCE_CALLTYPE createPluginFilter() {
    return new SetekhAudioProcessor();
}
