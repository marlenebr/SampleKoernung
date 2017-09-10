/*
  ==============================================================================

    Grain.cpp
    Created: 10 Sep 2017 2:30:26am
    Author:  marle

  ==============================================================================
*/

#include "Grain.h"

Grain::Grain(int onset, int length, int startPos): onset(onset), length(length), startPosition(startPos)
{


}

Grain::Grain(): onset(0), length(1000), startPosition(0)
{
	onset = 0;
	length = 0;
	startPosition = 0;
}

Grain::~Grain()
{
}


void Grain::processSample(AudioSampleBuffer& currentBuffer, AudioSampleBuffer& fileBuffer, int numChannels, int blockNumSamples, int fileNumSamples, int time)
{
		for (int channel = 0; channel < numChannels; ++channel)
		{
			float* channelData = currentBuffer.getWritePointer(channel);
			const float* fileData = fileBuffer.getReadPointer(channel%fileBuffer.getNumChannels());

			int position = (time - onset) + startPosition;

			channelData[time % blockNumSamples] = fileData[position % fileNumSamples];
		}
}

