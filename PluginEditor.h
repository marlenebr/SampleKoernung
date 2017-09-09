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
class GranularSynthesisAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    GranularSynthesisAudioProcessorEditor (GranularSynthesisAudioProcessor&);
    ~GranularSynthesisAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	//void read(int, int,int64,bool,bool);




private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GranularSynthesisAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularSynthesisAudioProcessorEditor)
};
