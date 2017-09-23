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
	 ), Thread("AudioThread1"), 
		envMidParam(nullptr),
		envSustainParam(nullptr),
		envCurveParam(nullptr)
#endif
{
	//Parameter
	addParameter(envMidParam = new AudioParameterFloat("envCenter", "Envelope Center", 0.0f, 1.0f, 0.5f));
	addParameter(envSustainParam = new AudioParameterFloat("envSustain", "Envelope Sustain", 0.0f, 1.0f, 0.5f));
	addParameter(envCurveParam = new AudioParameterFloat("envCurve", "Envelope Curve", NormalisableRange<float>(-12, 12, 0.01, 1), 0.0f));



	String path = "C:\\000Daten\\eigene_samples\\2017\\08\\2sectest.wav";
	filePosition = 0;
	formatManager.registerBasicFormats();

	time = 0;
	timeOfGrain = 0;
	//grain = *new Grain(88200, 44100, 0);
	sampleRate = 44100;
	//nextGrainOnset = 88200;
	actualGrainLength = 441 * additionalLength;
	isGettingFaster = true;
	//variatingGrainLength(sampleRate); //startLenght is one sec

	//Grain grain = *new Grain(88200, 441, 0);
	//grains.add(Grain(88200, 441, 0));
	//grains.add(Grain(98200, 441, 22000));
	//grains.add(Grain(128200, 441, 0));
	//grains.add(Grain(238200, 441, 22000));
	//grains.add(Grain(58200, 441, 0));


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

	const int numSamplesInBlock = buffer.getNumSamples();

	// clear the buffer so we don't get any noise
	for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
		buffer.clear(i, 0, numSamplesInBlock);

	//Kopie des FileBuffers
	ReferenceCountedBuffer::Ptr retainedCurrentBuffer(fileBuffer);


	// finally get a AudioSampleBuffer we can use for processing ...von der File
	AudioSampleBuffer* currentAudioSampleBuffer(retainedCurrentBuffer->getAudioSampleBuffer());
	const int numSamplesInFile = currentAudioSampleBuffer->getNumSamples();

	const Array<Grain> localGrains = grains;


	for (int s = 0; s < numSamplesInBlock; ++s) {  
		for (int i = 0; i < localGrains.size(); ++i) {
				if (timeOfGrain <  localGrains[i].length *2) {
					//localGrains[i].processSample(buffer, *currentAudioSampleBuffer, buffer.getNumChannels(), numSamplesInBlock, numSamplesInFile, time,timeOfGrain);
					//overlap another grain
					localGrains[i].processSampleForGrainCombine(buffer, *currentAudioSampleBuffer, buffer.getNumChannels(), numSamplesInBlock, numSamplesInFile, time, timeOfGrain);

				}


			}
		timeOfGrain++;
		++time;
	}


    
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


}

//Update
void GranularSynthesisAudioProcessor::run()
{
	while (!threadShouldExit())
	{
		checkForBuffersToFree();
		checkForPathToOpen();
		int dur = 1000;

		// delete grains
		if (grains.size() > 0) {
			for (int i = grains.size() - 1; i >= 0; --i) {
				// check if the grain has ended
				long long int grainEnd = grains[i].length;
				bool hasEnded = grainEnd < timeOfGrain;

				if (hasEnded) grains.remove(i);
			}
		}

		// add grains
		else if (fileBuffer != nullptr) {
			// initialize nextGrainOnset to lie in the future
			//if (nextGrainOnset == 0) nextGrainOnset = time;

			int numSamples = fileBuffer->getAudioSampleBuffer()->getNumSamples();


			float trans = 2;
			trans += 1 + ((Random::getSystemRandom().nextFloat() * 2 - 1)) + transponseVal;

			float ratio = pow(2.0, trans / 12.0);

			// Duration


			// Length
			float density = (1 + ((Random::getSystemRandom().nextFloat() * 2 - 1)));
			int length = density * sampleRate * additionalLength;

			// Position
			float randPosition = (Random::getSystemRandom().nextFloat());
			int startPosition = (randPosition + additionalPosTranslate *sampleRate)* numSamples;
			startPosition = wrap(startPosition * sampleRate , 0, numSamples);

		   // startPosition += additionalPosTranslate *100;

			// Amplitude
			float amp = 0.8;
			//amp *= 1 + (Random::getSystemRandom().nextFloat() * 2 - 1);



			
			actualGrainLength = variatingGrainLength(actualGrainLength + additionalLength * sampleRate);

			grains.add(Grain(actualGrainLength, startPosition, ratio, amp));
			timeOfGrain = 0;

			wait(441 * additionalLength);

			}
			else 
			{
				// there are no held notes so we should reset the value for nextGrainOnset
				//nextGrainOnset = 0;
				wait(100);
			}
	}
}

//
//Grain GranularSynthesisAudioProcessor::TranslatedGrain(Grain gr)
//{
//	Grain tGrain = Grain(gr.length * 2, gr.startPos, gr.rate * 1.5, gr.amp);
//	return tGrain;
//}

int GranularSynthesisAudioProcessor::variatingGrainLength(int previousLen)
{

	int newLen = previousLen;


	if (newLen >= sampleRate)
		isGettingFaster = false;


	else if (newLen <441)
		isGettingFaster = true;


	if (isGettingFaster)
	{
		newLen += 441;
	}
	else
	{
		newLen -= 441;
	}


	return newLen;


}


int GranularSynthesisAudioProcessor::wrap(int val, const int low, const int high)
{
	int range_size = high - low + 1;

	if (val < low)
		val += range_size * ((low - val) / range_size + 1);

	return low + (val - low) % range_size;
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
