/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BruceA2AudioProcessorEditor::BruceA2AudioProcessorEditor (BruceA2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);


    addAndMakeVisible(volLabel);
    volLabel.setText("Volume", dontSendNotification);
    volLabel.attachToComponent(&volSlider, false);
    
    addAndMakeVisible(freqLabel);
    freqLabel.setText("Frequency", dontSendNotification);
    freqLabel.attachToComponent(&freqSlider, false);
    
    
    
    volSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 120);
    volSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    volSlider.setColour(Slider::ColourIds::rotarySliderFillColourId,Colours::indianred);
    volSlider.setRange(0,100,0);
    volSlider.setTextValueSuffix("dB");
    volSlider.addListener(this);
    addAndMakeVisible(volSlider);

    
    
    freqSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 90, 120);
    freqSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    freqSlider.setColour(Slider::ColourIds::rotarySliderFillColourId,Colours::indianred);
    freqSlider.setRange(20.0f,200.0f);
    freqSlider.setTextValueSuffix("Hz");
    freqSlider.addListener(this);
    addAndMakeVisible(freqSlider);
    //setResizable(true,true);
}

BruceA2AudioProcessorEditor::~BruceA2AudioProcessorEditor()
{
}

//==============================================================================
//workshop week 5

void BruceA2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::coral);
    g.setFont (random.nextFloat()* 24.0f + 12.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(),
                      Justification::centred, 1);
    
    g.setColour (Colours::firebrick);
    g.setFont(Font ("Comic Sans", 20.0f, Font::italic));
    
    
    g.setColour(Colours::cornflowerblue);
    g.setFont(40.0f);
    g.drawFittedText("Gooey Gui", 10, 10, getWidth(), 15, Justification::left, 1);
    
    g.setColour(Colours::gold);
    g.drawRect(150, 10, 250, 100);
    
    g.setColour(Colours::hotpink);
    g.drawLine(0.0f, 0.0f, getWidth(), getHeight());
}

void BruceA2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    //setting size of slider
    volSlider.setBounds(30, getHeight()-160, 150, 190);
    freqSlider.setBounds(300, getHeight()-80, 80, 80);
    
    
}
    // double check the slider bounds to make logical sense.
void BruceA2AudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &volSlider)
    {
        //get the value on the current slider, pass that value onto our processor
       // processor.mixLevel =mixSlider.getValue();
        processor.mixLevel.setTargetValue(volSlider.getValue());
    } else if (slider== &freqSlider) {
        
        
    }
    
}

