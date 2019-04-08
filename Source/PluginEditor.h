/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class BruceA2AudioProcessorEditor  : public AudioProcessorEditor, Slider::Listener
{
public:
    BruceA2AudioProcessorEditor (BruceA2AudioProcessor&);
    ~BruceA2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    Random random;
    
private:
    
//creating slider. 
    Slider volSlider;
    Slider freqSlider;
    
    Label freqLabel;
    Label volLabel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    void sliderValueChanged(Slider* slider) override;
    
    //BYE!!!
    
    
    BruceA2AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BruceA2AudioProcessorEditor)
};
