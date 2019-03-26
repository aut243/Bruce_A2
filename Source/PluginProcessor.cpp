/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BruceA2AudioProcessor::BruceA2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    currentSampleRate = 0.0f;
    currentAngle = 0.0f;
    angleDelta = 0.0f;
    sinFreq = 0.0f;
    
}

BruceA2AudioProcessor::~BruceA2AudioProcessor()
{
}

//==============================================================================
const String BruceA2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BruceA2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BruceA2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BruceA2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BruceA2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BruceA2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BruceA2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void BruceA2AudioProcessor::setCurrentProgram (int index)
{
}

const String BruceA2AudioProcessor::getProgramName (int index)
{
    return {};
}

void BruceA2AudioProcessor::changeProgramName (int index, const String& newName)
{
}





//==============================================================================
void BruceA2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    currentSampleRate = sampleRate;
    sinFreq= 1.0f;
    updateAngleDelta();
    
    String message;
    message<< "Preparing to play..." << newLine;
    //message<< "My sample rate is ...."
    
}

void BruceA2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BruceA2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BruceA2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    AudioBuffer<float> wetBuffer(totalNumInputChannels, buffer.getNumSamples());
    wetBuffer.makeCopyOf(buffer);
    
    //going through each channel of audio that is available
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //we are getting an audio block of size 512....
        auto* channelData = buffer.getWritePointer (channel);
        auto* wetData= wetBuffer.getWritePointer (channel);
        
        // ..do something to each audio sample....
        for ( int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            auto currentSinSample = (float) std::sin(currentAngle);
            currentAngle += angleDelta;
            wetData[sample] = wetData[sample] * 0.5f;//currentSinsample;
            
            auto shapedSample = jlimit((float) -0.8, (float) 0.8, wetData[sample]);
            wetData[sample] = shapedSample;
            
        
            
            
            channelData[sample] = channelData[sample] * 0.3f + wetData[sample] * 0.7f;
            channelData[sample] = jlimit ((float) -0.1, (float) 0.1, wetData[sample]);
            
        }
    }
}

//==============================================================================
bool BruceA2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BruceA2AudioProcessor::createEditor()
{
    return new BruceA2AudioProcessorEditor (*this);
}

//==============================================================================
void BruceA2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BruceA2AudioProcessor::updateAngleDelta()
{
    auto cyclesPerSample = sinFreq / currentSampleRate;
    angleDelta = cyclesPerSample = MathConstants<float>::twoPi;
    
}

void BruceA2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BruceA2AudioProcessor();
}

//ATTN: used a keys loop that sounded best
