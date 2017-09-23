/*
  ==============================================================================

    Grain.h
    Created: 10 Sep 2017 12:21:47am
    Author:  marle

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#ifndef GRAIN_H_INCLUDED
#define GRAIN_H_INCLUDED


class Grain 
{

public:

	//Grain(long long int, int, int, float, float, float, float, float);
	Grain(int, int, float, float);

	Grain();

	~Grain();


	const int length;
    const int startPos;
	const float rate;
	const float amp;

	float ampEnvelope(int, int);
	inline float cubicinterp(float, float, float, float, float);

	void processSample(AudioSampleBuffer&, AudioSampleBuffer&, int, int, int, int,int);
	void processSampleReverse(AudioSampleBuffer&, AudioSampleBuffer&, int, int, int, int);
	

private:
	//==============================================================================
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Grain)
};


#endif // GRAIN_H_INCLUDED