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

    Cell& getCell(int, int);
    void getStart(Cell&);
    void getEnd(Cell&);

    void moveCell(Cell cell);
    bool pathExists();
	int getDistance(Cell&, Cell&);

	void clearParents();
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
			CellsVector.at(i).setWalkable();

		if(CellsVector.at(i).getX() == x && CellsVector.at(i).getY() == y)
		{
			CellsVector.at(i).setIsStart();
		}
	}
}

void Grid::setEnd(int x, int y)
{
	for(int i = 0; i < CellsVector.size(); i++)
	{
		if(CellsVector.at(i).IsEnd())
			CellsVector.at(i).setWalkable();

		if(CellsVector.at(i).getX() == x && CellsVector.at(i).getY() == y)
		{
			CellsVector.at(i).setIsEnd();
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
				CellsVector.at(i).setObstacle();
			else
			{
				CellsVector.at(i).setWalkable();
				break;
			}	
		}
	}
}

Cell &Grid::getCell(int x, int y)
{
    for(int i = 0; i < CellsVector.size(); i++) 
    {
        if(CellsVector.at(i).getX() == x && CellsVector.at(i).getY() == y)
            return CellsVector.at(i);
    }

    return *CellsVector.end();
}

void Grid::getStart(Cell& start)
{
	for(int i = 0; i < CellsVector.size(); i++)
	{
		if(CellsVector.at(i).IsStart())
			start = CellsVector.at(i);
	} 
}

void Grid::getEnd(Cell& end)
{
	for(int i = 0; i < CellsVector.size(); i++)
	{
		if(CellsVector.at(i).IsEnd())
			end = CellsVector.at(i);
	} 
}

bool Grid::pathExists()
{
    Cell start, end;
	getStart(start);
	getEnd(end);
    if(start.IsStart() && end.IsEnd())
        return true;

    return false;
}

void Grid::moveCell(Cell cell)
{
	for(int i = 0; i < CellsVector.size(); i++)
	{
		if(cell == CellsVector.at(i))
			{
				CellsVector.at(i) = cell;
				break;
			}
	}
}

void Grid::clearParents()
{
	for(int i = 0; i < CellsVector.size(); i++)
	{
		CellsVector.at(i).clearParent();
	}
}

int Grid::getDistance(Cell& cell1, Cell& cell2)
{
	int x = abs(cell1.getX() - cell2.getX());
	int y = abs(cell1.getY() - cell2.getY());

	if(x > y)
		return 14*y + 10*(x - y);
	
	return 14*x + 10*(y - x);
}