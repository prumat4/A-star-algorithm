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

    void GetMouseCoordinates(int& , int&);
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

void PathFinding::GetMouseCoordinates(int& x, int& y)
{	
	SDL_GetMouseState(&x, &y);

	int tempX = x % CELL_SIZE;
	int tempY = y % CELL_SIZE;
	
	x -= tempX;
	y -= tempY;
	
	x = x / CELL_SIZE;
	y = y / CELL_SIZE;
}
