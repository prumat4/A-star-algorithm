#pragma once

#include "cell.hpp"

class Grid
{
    std::vector<Cell> CellsVector;
public:
    Grid();

    auto getCellsVector() { return CellsVector; }


    void setStart(int, int);
    void setEnd(int, int);    
    void setObstacle(int, int);
};

Grid::Grid()
{
    for(int i = 0; i < WINDOW_WIDTH / CELL_SIZE; i++)
        for(int j = 0; j < WINDOW_HEIGHT / CELL_SIZE; j++)
        {
            Cell temporaryCell(i, j);
            CellsVector.push_back(temporaryCell);
        }

}

void Grid::setStart(int x, int y)
{
	for(int i = 0; i < CellsVector.size(); i++)
	{
		if(CellsVector.at(i).IsStart())
			CellsVector.at(i).SetWalkable();

		if(CellsVector.at(i).getX() == x && CellsVector.at(i).getY() == y)
		{
			CellsVector.at(i).SetIsStart();
		}
	}
}

void Grid::setEnd(int x, int y)
{
	for(int i = 0; i < CellsVector.size(); i++)
	{
		if(CellsVector.at(i).IsEnd())
			CellsVector.at(i).SetWalkable();

		if(CellsVector.at(i).getX() == x && CellsVector.at(i).getY() == y)
		{
			CellsVector.at(i).SetIsEnd();
		}
	}
}

void Grid::setObstacle(int x, int y)
{
	for(int i = 0; i < CellsVector.size(); i++)
	{
		if(CellsVector.at(i).getX() == x && CellsVector.at(i).getY() == y)
		{	
			if(CellsVector.at(i).IsWalkable())
				CellsVector.at(i).SetObstacle();
			else
			{
				CellsVector.at(i).SetWalkable();
				break;
			}	
		}
	}
}
