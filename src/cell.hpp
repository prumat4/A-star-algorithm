#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define SIZE 30

class Cell
{
public:
    int x;
    int y;

    bool walkable;
    bool isStart;
    bool isEnd;
    bool isInPath;

    int hCost;
    int gCost;

    Cell* parent;


    Cell();
    
    bool operator == (const Cell&);
    bool operator != (const Cell&);

    Cell& operator = (const Cell&);
    
    int fCost();

    void SetIsStart();
	void SetIsEnd();
	void SetWalkable();
	void SetObstacle();
	void SetIsInPath();
};

Cell::Cell()
{
	x = 0;
	y = 0;
	
	walkable = true;
	isStart = false;
	isEnd = false;
	isInPath = false;

    hCost = 0;
    gCost = 0;

	parent = nullptr;
}

bool Cell::operator ==(const Cell &cell)
{ 
    if(this->x == cell.x && this->y == cell.y)
        return true;
    return false;
}

bool Cell::operator ==(const Cell &cell)
{ 
    return !(*this == cell);
}

Cell &Cell::operator=(const Cell &cell)
{
    this->x = cell.x;
    this->y = cell.y;

    this->walkable = cell.walkable;
    this->isEnd = cell.isEnd;
    this->isStart = cell.isEnd;
    this->isInPath = cell.isInPath;

    this->hCost = cell.hCost;
    this->gCost = cell.gCost;

    this->parent = cell.parent;
}

int Cell::fCost()
{
    return gCost + hCost;
}

void Cell::SetIsStart()
{
	isStart = true;
	isEnd = false;
	walkable = true;
	isInPath = false;
}

void Cell::SetIsEnd()
{
	isEnd = true;
	isStart = false;
	walkable = true;
	isInPath = false;
}

void Cell::SetWalkable()
{
    isEnd = false;
    isStart = false;
    walkable = true;
	isInPath = false;
}

void Cell::SetObstacle()
{
    isEnd = false;
    isStart = false;
    walkable = false;
	isInPath = false;
}

void Cell::SetIsInPath()
{
	isEnd = false;
    isStart = false;
    walkable = true;
	isInPath = true;
}