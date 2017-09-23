/*
  ==============================================================================

    Grain.cpp
    Created: 10 Sep 2017 2:30:26am
    Author:  marle

  ==============================================================================
*/

#include "Grain.h"


Grain::Grain(int length, int startPos, int rate, float amp) : length(length), startPosition(startPos), rate(rate), amp(amp)
{


}



Grain::Grain() : length(1000), startPosition(0), rate(1), amp(1)
{

}
Grain::~Grain()
{
}


void Grain::processSample(AudioSampleBuffer& currentBuffer, AudioSampleBuffer& fileBuffer, int numChannels, int blockNumSamples, int fileNumSamples, int time)
{


	for (int channel = 0; channel < numChannels; ++channel) {
		//const float gain = envelope(time);

		float* channelData = currentBuffer.getWritePointer(channel);
		const float* fileData = fileBuffer.getReadPointer(channel%fileBuffer.getNumChannels());

		const float position = time * rate;

		const int iPosition = (int)std::ceil(position);

		//const float fracPos = position - iPosition;

		const int readPos = iPosition + startPosition;

		float currentSample = fileData[readPos % fileNumSamples];

		currentSample = currentSample * amp;

		channelData[time % blockNumSamples] += currentSample;
	}

}

//float Grain::envelope(int time)
//{
//		float gain = 0;
//		float envPos = 0;
//
//		envPos = (time - onset) * lengthRecip;
//
//		if (envPos <= envAttack)
//		{
//			if (std::abs(envCurve) > 0.001)
//			{
//				float aPos;
//
//				aPos = envPos * envAttackRecip;
//
//				double denom = 1.0f - exp(envCurve);
//				double numer = 1.0f - exp(aPos * envCurve);
//
//				gain = (numer / denom);
//			}
//			else
//			{
//				float aPos;
//
//				aPos = envPos * envAttackRecip;
//				gain = aPos;
//			}
//		}
//		else if (envPos < envRelease)
//		{
//			gain = 1.0;
//
//		}
//		else if (envPos >= envRelease)
//		{
//			if (std::abs(envCurve) > 0.001)
//			{
//				float rPos;
//
//				rPos = (envPos - envRelease) * envReleaseRecip;
//
//				double denom = 1.0f - exp(-envCurve);
//				double numer = 1.0f - exp(rPos * -envCurve);
//
//				gain = (numer / denom) * (-1) + 1;
//			}
//			else {
//				float rPos;
//
//				rPos = (envPos - envRelease) * envReleaseRecip;
//				gain = rPos * (-1) + 1;
//			}
//		}
//		return gain;
//	
//}

inline float Grain::cubicinterp(float x, float y0, float y1, float y2, float y3)
{
		// 4-point, 3rd-order Hermite (x-form)
		float c0 = y1;
		float c1 = 0.5f * (y2 - y0);
		float c2 = y0 - 2.5f * y1 + 2.f * y2 - 0.5f * y3;
		float c3 = 0.5f * (y3 - y0) + 1.5f * (y1 - y2);

		return ((c3 * x + c2) * x + c1) * x + c0;


}
void Grain::processSampleReverse(AudioSampleBuffer& currentBuffer, AudioSampleBuffer& fileBuffer, int numChannels, int blockNumSamples, int fileNumSamples, int time)
{
	for (int channel = 0; channel < numChannels; ++channel)
	{
		float* channelData = currentBuffer.getWritePointer(channel);
		const float* fileData = fileBuffer.getReadPointer(channel%fileBuffer.getNumChannels());

		//int position = (time - onset) + startPosition;
		int position = time + startPosition;

		channelData[blockNumSamples-(time % blockNumSamples)] = fileData[position % fileNumSamples];
	}
}

