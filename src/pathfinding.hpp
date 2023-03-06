#pragma once

#include "grid.hpp"

class PathFinding
{
    Grid grid;
public:
    Grid getGrid() { return grid; }

    void setStart(int, int);
    void setEnd(int, int);
    void setObstacle(int, int);

    void getMouseCoordinates(int& , int&);

    std::vector<Cell> getNeighbours(Cell);
    void clearPath();
    void setPath(std::vector<Cell>);
};

void PathFinding::setStart(int x, int y)
{
    grid.setStart(x, y);
}

void PathFinding::setEnd(int x, int y)
{
    grid.setEnd(x, y);
}

void PathFinding::setObstacle(int x, int y)
{
    grid.setObstacle(x, y);
}

void PathFinding::getMouseCoordinates(int& x, int& y)
{	
	SDL_GetMouseState(&x, &y);

	int tempX = x % CELL_SIZE;
	int tempY = y % CELL_SIZE;
	
	x -= tempX;
	y -= tempY;
	
	x = x / CELL_SIZE;
	y = y / CELL_SIZE;
}

std::vector<Cell> PathFinding::getNeighbours(Cell cell)
{
    std::vector<Cell> neighbours;

    for(int i = -1; i <= 1; i++)
    { 
        for(int j = -1; j <= 1; j++)
        {
            if(i == 0 && j == 0)
                continue;
            
            int x = cell.getX() + i;
            int y = cell.getY() + j;

            if(x >= 0 && x < (WINDOW_WIDTH / CELL_SIZE) && 
			   y >= 0 && y < (WINDOW_HEIGHT / CELL_SIZE))
                {
					Cell temporary = grid.getCell(x, y);
					
					if(temporary.IsWalkable())
						neighbours.push_back(temporary);
				}
        }
    }

    return neighbours;
}

void PathFinding::clearPath()
{
    for(auto cell: grid.getCellsVector())
    {
        cell.setWalkable();
        grid.moveCell(cell);
    }
}

void PathFinding::setPath(std::vector<Cell> path)
{
    clearPath();

    for(auto cell: path)
    {
        cell.setIsInPath();
        grid.moveCell(cell);
    }
}