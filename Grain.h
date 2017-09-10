/*
  ==============================================================================

    Grain.h
    Created: 10 Sep 2017 12:21:47am
    Author:  marle

  ==============================================================================
*/

#pragma once



class Grain
{

public:
	Grain() {};
	~Grain() {};

	void processSample(AudioSampleBuffer& currentBuffer, AudioSampleBuffer& fileBuffer, int numChannels, int blockNumSamples, int fileNumSamples, int time)
	{
		for (int channel = 0; channel < numChannels; ++channel)
		{

			for (int channel = 0; channel < numChannels; ++channel) 
			{
				float* channelData = currentBuffer.getWritePointer(channel);
				const float* fileData = fileBuffer.getReadPointer(channel%fileBuffer.getNumChannels());

				channelData[time%blockNumSamples] += fileData[time%fileNumSamples];
			}
		}



	}
};
