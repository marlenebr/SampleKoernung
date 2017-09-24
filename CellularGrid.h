/*
  ==============================================================================

    CellularRow.h
    Created: 24 Sep 2017 1:31:40am
    Author:  marle

  ==============================================================================
*/


#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#ifndef CELLULARGRID_H_INCLUDED
#define CELLULARGRID_H_INCLUDED


class CellularGrid
{

public:

	//Grain(long long int, int, int, float, float, float, float, float);
	CellularGrid(int,int);

	CellularGrid();

	~CellularGrid();


	int rows;
	int columns;


	Array<bool> gridData;

	bool cellState;

	bool getCell(int, int);
	int getCellIndex(int, int);
	bool getAliveNeighbours(int row, int col);
	void processGrid(AudioSampleBuffer&, AudioSampleBuffer&, int, int, int, int, int);



private:
	//==============================================================================
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CellularRow)
};


#endif // CELLULARROW_H_INCLUDED
