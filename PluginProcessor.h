/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ReferenceCountedBuffer.h"
#include "Grain.h"




//==============================================================================
/**
*/
class GranularSynthesisAudioProcessor  : public AudioProcessor,
											public Thread
										
{
public:
    //==============================================================================
    GranularSynthesisAudioProcessor();
    ~GranularSynthesisAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;


	//Samplebuffer
	//AudioSampleBuffer fileBuffer;
	int filePosition; //index für samples
	AudioFormatManager formatManager;

	ReferenceCountedArray<ReferenceCountedBuffer> buffers;

	ReferenceCountedBuffer::Ptr fileBuffer;

	//Load File
	void checkForPathToOpen();
	String chosenPath;


	//Values from UI
	double durationVal;
	double TransponseVal;
	double OtherEffektTest;


	

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void loadAudioFile(String);

	void checkForBuffersToFree();

	int variatingGrainLength(int);

	void run() override;

	int wrap(int, const int, const int);

	// Envelope Parameters:
	AudioParameterFloat* envMidParam;
	AudioParameterFloat* envSustainParam;
	AudioParameterFloat* envCurveParam;

	//Granular

	int time;
	int timeOfGrain;
	double sampleRate;
	int actualGrainLength;

	bool isGettingFaster;

	//long long int nextGrainOnset;



	//Array<Grain> grainStack;
	//Grain grain;
	Array<Grain> grains;





private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularSynthesisAudioProcessor)
};
