/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Grain.h"


//==============================================================================
GranularSynthesisAudioProcessor::GranularSynthesisAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
	 ), Thread("AudioThread1")
#endif
{
	String path = "C:\\000Daten\\eigene_samples\\2017\\08\\2sectest.wav";
	filePosition = 0;
	formatManager.registerBasicFormats();

	time = 0;
	//grain = *new Grain(88200, 44100, 0);
	sampleRate = 44100;
	nextGrainOnset = 88200;

	Grain grain = *new Grain(88200, 44100, 0);
	grains.add(Grain(88200, 44100, 0));
	grains.add(Grain(98200, 88100, 0));
	grains.add(Grain(128200, 5100, 0));
	grains.add(Grain(238200, 124100, 0));
	grains.add(Grain(58200, 42100, 0));


	//localGrains = *new Array<Grain> grains; //Copying Grain-array


	startThread();

 //2sec,1sec,0

	loadAudioFile(path);

}

GranularSynthesisAudioProcessor::~GranularSynthesisAudioProcessor()
{
	stopThread(4000);

}


//==============================================================================
const String GranularSynthesisAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GranularSynthesisAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GranularSynthesisAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double GranularSynthesisAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GranularSynthesisAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GranularSynthesisAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GranularSynthesisAudioProcessor::setCurrentProgram (int index)
{
}

const String GranularSynthesisAudioProcessor::getProgramName (int index)
{
    return {};
}

void GranularSynthesisAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GranularSynthesisAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GranularSynthesisAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GranularSynthesisAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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


//Buffer hat alle Channels und ist input welche für den output überschrieben wwird
void GranularSynthesisAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	const int totalNumInputChannels = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.


	//Kopie des FileBuffers
	ReferenceCountedBuffer::Ptr retainedCurrentBuffer(fileBuffer);


	// finally get a AudioSampleBuffer we can use for processing ...von der File
	AudioSampleBuffer* currentAudioSampleBuffer(retainedCurrentBuffer->getAudioSampleBuffer());
	int position = retainedCurrentBuffer->position; //0 - 442 --884 usw

	const int numInputChannels = currentAudioSampleBuffer->getNumChannels();
	const int numOutputChannels = buffer.getNumChannels();


	int outputSamplesRemaining = buffer.getNumSamples();
	const int numSamplesInFile = currentAudioSampleBuffer->getNumSamples();
	int outputSamplesOffset = 0;



	int bufferSamplesRemaining = currentAudioSampleBuffer->getNumSamples() - position; //Komplete samplesanzahl von file - bisher vergangene samples
	int samplesThisTime = jmin(outputSamplesRemaining, bufferSamplesRemaining); //am ende könnten weniger samples drin sein, nimmt den kleineren der beiden werte

	for (int channel = 0; channel < numOutputChannels; ++channel)
	{
		buffer.copyFrom(channel,
			outputSamplesOffset,
			*currentAudioSampleBuffer,
			channel % numInputChannels,
			position,
			samplesThisTime);
	}

	for (int sample = 0; sample < outputSamplesRemaining; ++sample)
	{
		//grain.processSample(buffer, *currentAudioSampleBuffer, buffer.getNumChannels(), outputSamplesRemaining, numSamplesInFile, time);
		for (int i = 0; i < localGrains.size(); ++i) {
			if (grains[i].onset < time) {
				if (time < (grains[i].onset + grains[i].length)) {
					grains[i].processSample(buffer, *currentAudioSampleBuffer, buffer.getNumChannels(), outputSamplesRemaining, numSamplesInFile, time);
				}
			}
		}
		++time;
	}

	outputSamplesRemaining -= samplesThisTime;  //0 ausser am ende, dann weniger (den kehrwehrt von outputsampleoffset
	outputSamplesOffset += samplesThisTime; //442 ausser am ende einmal, dann weniger
	position += samplesThisTime; //pos + 442 

	if (position == currentAudioSampleBuffer->getNumSamples()) //dann ist das ende erreicht
		position = 0;
   

	retainedCurrentBuffer->position = position; //wiedr auf pos 0 setzen, anfang


        // ..do something to the data...
    
}

//==============================================================================
bool GranularSynthesisAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GranularSynthesisAudioProcessor::createEditor()
{
    return new GranularSynthesisAudioProcessorEditor (*this);
}

//==============================================================================
void GranularSynthesisAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GranularSynthesisAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void GranularSynthesisAudioProcessor::loadAudioFile(String path)
{
	const File file(path);

	//Pointer auf Reader und Audiosamples mit der ScopedPointer Klasse, welche das mit den Pointern einfacher macht
	ScopedPointer<AudioFormatReader> reader(formatManager.createReaderFor(file));
	//ScopedPointer<AudioSampleBuffer> newBuffer = new AudioSampleBuffer(reader->numChannels, reader->lengthInSamples); //Audiobuffer mit den gleichen einstellungen einstellungen wie die file
	if (reader != nullptr)
	{
		const double duration = reader->lengthInSamples / reader->sampleRate;

		if (duration < 2)
		{
			ReferenceCountedBuffer::Ptr newBuffer = new ReferenceCountedBuffer(file.getFileName(),
				reader->numChannels,
				reader->lengthInSamples);

			reader->read(newBuffer->getAudioSampleBuffer(), 0, reader->lengthInSamples, 0, true, true);
			fileBuffer = newBuffer;
			buffers.add(newBuffer);
		}
		else
		{
			// handle the error that the file is 2 seconds or longer..
		}
	}


	//std::cout << "samples in buffer: " << newBuffer->getAudioSampleBuffer()->getNumSamples() << std::endl;
	//fileBuffer = newBuffer;


}

//Update
void GranularSynthesisAudioProcessor::run()
{
	while (!threadShouldExit())
	{
		checkForBuffersToFree();
		checkForPathToOpen();
		wait(500);
	}
}

void GranularSynthesisAudioProcessor::checkForBuffersToFree()
{
	for (int i = buffers.size(); --i >= 0;)                           
	{
		ReferenceCountedBuffer::Ptr buffer(buffers.getUnchecked(i));

		if (buffer->getReferenceCount() == 2)        
			buffers.remove(i);
	}
}

void GranularSynthesisAudioProcessor::checkForPathToOpen()
{
	String pathToOpen;
	swapVariables(pathToOpen, chosenPath);

	if (pathToOpen.isNotEmpty())
	{
		const File file(pathToOpen);
		ScopedPointer<AudioFormatReader> reader(formatManager.createReaderFor(file));

		if (reader != nullptr)
		{
			const double duration = reader->lengthInSamples / reader->sampleRate;

			if (duration < 2)
			{
				ReferenceCountedBuffer::Ptr newBuffer = new ReferenceCountedBuffer(file.getFileName(), reader->numChannels, reader->lengthInSamples);
				reader->read(newBuffer->getAudioSampleBuffer(), 0, reader->lengthInSamples, 0, true, true);
				fileBuffer = newBuffer;
				buffers.add(newBuffer);
			}
			else
			{
				// handle the error that the file is 2 seconds or longer..
			}
		}
	}
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GranularSynthesisAudioProcessor();
}
