/*
  ==============================================================================

    ReferenceCountedBuffer.h
    Created: 21 Aug 2017 3:08:13pm
    Author:  marle

  ==============================================================================
*/

#pragma once


class ReferenceCountedBuffer : public ReferenceCountedObject
{
public:
	typedef ReferenceCountedObjectPtr<ReferenceCountedBuffer> Ptr;

	ReferenceCountedBuffer(const String& nameToUse,
		int numChannels,
		int numSamples)
		: position(0),
		name(nameToUse),
		buffer(numChannels, numSamples)
	{
		DBG(String("Buffer named '") + name + "' constructed. numChannels = " + String(numChannels) + ", numSamples = " + String(numSamples));
	}

	~ReferenceCountedBuffer()
	{
		DBG(String("Buffer named '") + name + "' destroyed");
	}

	AudioSampleBuffer* getAudioSampleBuffer()
	{
		return &buffer;
	}

	int position;

private:
	String name;
	AudioSampleBuffer buffer;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReferenceCountedBuffer)
};