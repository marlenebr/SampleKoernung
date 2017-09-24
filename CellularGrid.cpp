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
			gridData[row,     col], //middle, should be true
			gridData[row,     col + 1],
		},
		{
			gridData[row + 1, col - 1],
			gridData[row + 1, col],
			gridData[row + 1, col + 1]
		}
	};

}

//int CellularGrid::getCellIndex(int row, int col)
//{
//	row = rows%row;
//	col = columns%col;
//
//	int result = (row * columns) + col;
//	return result;
//}
