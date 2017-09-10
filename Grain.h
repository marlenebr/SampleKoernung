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

	Grain(long long int, int, int, float, float, float, float, float);
	Grain();
	~Grain();


	const long long int onset;
	const int length;
	const int startPosition;

	const float envAttack, envAttackRecip;
	const float envRelease, envReleaseRecip;
	const float envCurve;
	const float lengthRecip;

	const float rate;
	const float amp;


	inline float cubicinterp(float, float, float, float, float);
	float envelope(int);

	void processSample(AudioSampleBuffer&, AudioSampleBuffer&, int, int, int, int);
	void processSampleReverse(AudioSampleBuffer&, AudioSampleBuffer&, int, int, int, int);
	

private:
	//==============================================================================
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Grain)
};


#endif // GRAIN_H_INCLUDED