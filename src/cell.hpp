#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <vector>
#include <algorithm>
#include <math.h>

#define CELL_SIZE 30
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class Cell
{
    int x;
    int y;

    bool walkable;
    bool isStart;
    bool isEnd;
    bool isInPath;

    int hCost;
    int gCost;

    int parentX;
    int parentY;
    SDL_Rect sdl_rect;

public:
    Cell();
    Cell(const int, const int);
    
    bool operator == (const Cell&) const;
    bool operator != (const Cell&) const;

    Cell& operator = (const Cell&);
    
    int fCost();

    void setGCost(int);
    void setHCost(int);

    int getX() { return x; }
    int getY() { return y; }
    
    int getParentX() { return parentX; }
    int getParentY() { return parentY; }

    void setParent(Cell&);

    int getHCost() { return hCost; }
    int getGCost() { return gCost; }

    bool IsStart() { return isStart; }
    bool IsEnd() { return isEnd; }
    
    bool IsWalkable() { return walkable; }
    bool IsInPath() { return isInPath; }

    SDL_Rect getRect() { return sdl_rect; }

    void setIsStart();
	void setIsEnd();
	void setWalkable();
	void setObstacle();
	void setIsInPath();
};

Cell::Cell()
{
	x = 0;
	y = 0;
    
    parentX = x;
    parentY = y;

	walkable = true;
	isStart = false;
	isEnd = false;
	isInPath = false;

    hCost = 0;
    gCost = 0;

    sdl_rect.x = x * CELL_SIZE;
    sdl_rect.y = y * CELL_SIZE;
    sdl_rect.w = sdl_rect.h = CELL_SIZE;

}

Cell::Cell(int x, int y)
{
    this->x = x;
	this->y = y;
	
    parentX = x;
    parentY = y;

	walkable = true;
	isStart = false;
	isEnd = false;
	isInPath = false;

    hCost = 0;
    gCost = 0;

    sdl_rect.x = x * CELL_SIZE;
    sdl_rect.y = y * CELL_SIZE;
    sdl_rect.w = sdl_rect.h = CELL_SIZE;
}

bool Cell::operator ==(const Cell &cell) const
{ 
    if(this->x == cell.x && this->y == cell.y)
        return true;
    return false;
}

bool Cell::operator !=(const Cell &cell) const
{ 
    return !(*this == cell);
}

Cell &Cell::operator =(const Cell &cell)
{
    this->x = cell.x;
    this->y = cell.y;

    this->walkable = cell.walkable;
    this->isEnd = cell.isEnd;
    this->isStart = cell.isStart;
    this->isInPath = cell.isInPath;

    this->hCost = cell.hCost;
    this->gCost = cell.gCost;

    this->sdl_rect = cell.sdl_rect;

    this->parentX = cell.parentX;
    this->parentY = cell.parentY;

    return *this;
}

void Cell::setParent(Cell& parent)
{
    this->parentX = parent.x;
    this->parentY = parent.y;
}

int Cell::fCost()
{
    return gCost + hCost;
}

void Cell::setGCost(int cost)
{
    gCost = cost;
}

void Cell::setHCost(int cost)
{
    hCost = cost;
}

void Cell::setIsStart()
{
	isStart = true;
	isEnd = false;
	walkable = true;
	isInPath = false;
}

void Cell::setIsEnd()
{
	isEnd = true;
	isStart = false;
	walkable = true;
	isInPath = false;
}

void Cell::setWalkable()
{
    isEnd = false;
    isStart = false;
    walkable = true;
	isInPath = false;
}

void Cell::setObstacle()
{
    isEnd = false;
    isStart = false;
    walkable = false;
	isInPath = false;
}

void Cell::setIsInPath()
{
	isEnd = false;
    isStart = false;
    walkable = true;
	isInPath = true;
}