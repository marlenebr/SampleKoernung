/*
  ==============================================================================

    CellularRow.cpp
    Created: 24 Sep 2017 11:30:38pm
    Author:  marle

  ==============================================================================
*/

#include "CellularRow.h"

CellularRow::CellularRow(int cells, int grainLength, float srate) : cellCount(cells), lengthInSamples(grainLength),rate(srate)
{
	rowData[cellCount];
	rowData = { false }; //all initialised to false

}

CellularRow::CellularRow(bool cellValues[], int grainLength, float srate) : cellCount(16), lengthInSamples(grainLength), rate(srate)
{
	rowData[cellCount];
	rowData = cellValues;

}




CellularRow::CellularRow() : cellCount(16)
{

}


CellularRow::~CellularRow()
{
}

bool CellularRow::getCell(int row)
{
	return rowData[row];
}


bool* CellularRow::getAliveNeighbours(int pos)
{
	bool neighbours [3];

	if (pos == 0)
	{
		neighbours[0] = rowData[cellCount];
	}
	else
	{
		neighbours[0] = rowData[cellCount % (pos - 1 + cellCount)];
	}
	neighbours[1] = rowData[pos];


	neighbours[2] = rowData[cellCount %(pos + 1 + cellCount)];

			//rowData[cellCount%(pos - 1)],
			//rowData[cellCount % pos],
			//rowData[cellCount % (pos + 1)] };

	return neighbours;

}

void CellularRow::processRow(AudioSampleBuffer& buffer, AudioSampleBuffer& fileBuffer, int numChannels, int blockNumSamples, int time)
{
	//Get The Sample and add it with itself with tranponse 
	const int samplesInFile = fileBuffer.getNumSamples();

	for (int channel = 0; channel < numChannels; ++channel) {

		float* channelDataWrite = buffer.getWritePointer(channel);
		const float* fileData = fileBuffer.getReadPointer(channel%fileBuffer.getNumChannels());

		
		float newSamples [16] = {};

		for (int i = 0; i < cellCount; i++)
		{
			if (rowData[i] == true && i<8)
			{

				int pos = (int)(std::ceil(time * rate * (8 - i)*0.2));

				newSamples[i] = fileData[pos % samplesInFile] / cellCount;

			}
			else if (rowData[i] == true && i>=8)
			{
				int pos = (int)(std::ceil(time* rate *(1 + ((i - 8)*0.2))));

				newSamples[i] = fileData[pos % samplesInFile] / cellCount;

			}
			else
			{
				//newSamples[i] = fileData[(int)(std::ceil(time* rate)) % samplesInFile] / cellCount;
				newSamples[i] = 0.0;

			}
		//newSamples[i] = fileData[(int)(std::ceil(time* rate)) % samplesInFile] / cellCount;
		}

		for (int i = 0; i < cellCount; i++)
		{
			channelDataWrite[time % blockNumSamples] += newSamples[i];
		}
	}



}

bool* CellularRow::getNextRow()
{

	bool* nextRow= rowData;

	for(int i = 0; i< sizeof(rowData);i++)
	{
		nextRow[i] = (getRuleValue(getAliveNeighbours(i)));

	}

	return nextRow;
}


bool CellularRow::getRuleValue(bool cellWithNeighbours[])
{

	//rule 90

	if (cellWithNeighbours[0] && cellWithNeighbours[1] && cellWithNeighbours[2])
	{
		return false;
	}
	else if (cellWithNeighbours[0] && cellWithNeighbours[1] && !cellWithNeighbours[2])
	{
		return true;
	}

	else if (cellWithNeighbours[0] && !cellWithNeighbours[1] && cellWithNeighbours[2])
	{
		return false;
	}

	else if (cellWithNeighbours[0] && !cellWithNeighbours[1] && !cellWithNeighbours[2])
	{
		return true;
	}

	else if (!cellWithNeighbours[0] && cellWithNeighbours[1] && cellWithNeighbours[2])
	{
		return true;
	}

	else if (!cellWithNeighbours[0] && cellWithNeighbours[1] && !cellWithNeighbours[2])
	{
		return false;
	}
	else if (!cellWithNeighbours[0] && !cellWithNeighbours[1] && cellWithNeighbours[2])
	{
		return true;
	}

	else if (!cellWithNeighbours[0] && !cellWithNeighbours[1] && !cellWithNeighbours[2])
	{
		return false;
	}



}





