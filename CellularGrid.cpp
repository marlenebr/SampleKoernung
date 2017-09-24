/*
  ==============================================================================

    CellularRow.cpp
    Created: 24 Sep 2017 1:31:15am
    Author:  marle

  ==============================================================================
*/

#include "CellularGrid.h"

CellularGrid::CellularGrid(int rowCount, int columnCount) : rows(rowCount), columns(columnCount)
{
	gridData[rowCount, columnCount];
	gridData = { {false} }; //all initialised to false

}



CellularGrid::CellularGrid() : rows(8), columns(8)
{

}


CellularGrid::~CellularGrid()
{
}

bool CellularGrid::getCell(int row, int col)
{
	return gridData[row, col];
}


bool CellularGrid::getAliveNeighbours(int row, int col)
{
	bool neighbours[3][3] = {
		{
			gridData[row - 1, col - 1],
			gridData[row - 1, col],
			gridData[row - 1, col + 1]},
		{
			gridData[row,     col - 1],
			gridData[row,     col], //middle
			gridData[row,     col + 1],
		},
		{
			gridData[row + 1, col - 1],
			gridData[row + 1, col],
			gridData[row + 1, col + 1]
		}
	};

	return neighbours;

}

