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

	Grain(int, int, int);
	Grain();
	~Grain();


	int onset;
	int length;
	int startPosition;

	void processSample(AudioSampleBuffer&, AudioSampleBuffer&, int, int, int, int);
	

private:
	//==============================================================================
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Grain)
};


#endif // GRAIN_H_INCLUDED