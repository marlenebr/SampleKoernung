/*
  ==============================================================================

    CellularRow.h
    Created: 24 Sep 2017 11:30:56pm
    Author:  marle

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#ifndef CELLULARROW_H_INCLUDED
#define CELLULARROW_H_INCLUDED


class CellularRow
{

public:

	CellularRow(int);

	CellularRow();

	~CellularRow();


	int cellCount;


	Array<bool> rowData;

	bool cellState;

	bool getCell(int);
	bool getAliveNeighbours(int row);
	void processRow(AudioSampleBuffer&, AudioSampleBuffer&, int, int, int, int, int);



private:
	//==============================================================================
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CellularRow)
};


#endif // CELLULARROW_H_INCLUDED
