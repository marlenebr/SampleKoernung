/*
  ==============================================================================

    CellularRow.cpp
    Created: 24 Sep 2017 11:30:38pm
    Author:  marle

  ==============================================================================
*/

#include "CellularRow.h"

CellularRow::CellularRow(int cells) : cellCount(cells)
{
	rowData[cellCount];
	rowData = { { false } }; //all initialised to false

}



CellularRow::CellularRow() : cellCount(8)
{

}


CellularRow::~CellularRow()
{
}

bool CellularRow::getCell(int row)
{
	return rowData[row];
}


bool CellularRow::getAliveNeighbours(int row)
{
	bool neighbours[3] = {
			rowData[row - 1],
			rowData[row],
			rowData[row + 1] };

	return neighbours;

}

