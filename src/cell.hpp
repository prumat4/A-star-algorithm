#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <vector>

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

    Cell* parent;
    SDL_Rect sdl_rect;

public:
    Cell();
    Cell(const int, const int);
    
    bool operator == (const Cell&);
    bool operator != (const Cell&);

    Cell& operator = (const Cell&);
    
    int fCost();

    int getX() { return x; }
    int getY() { return y; }
    int getHCost() { return hCost; }
    int getGCost() { return gCost; }

    bool IsWalkable() { return walkable; }
    bool IsStart() { return isStart; }
    bool IsEnd() { return isEnd; }
    bool IsInPath() { return isInPath; }

    Cell* getParent() { return parent; }
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
	
	walkable = true;
	isStart = false;
	isEnd = false;
	isInPath = false;

    hCost = 0;
    gCost = 0;

    sdl_rect.x = x * CELL_SIZE;
    sdl_rect.y = y * CELL_SIZE;
    sdl_rect.w = sdl_rect.h = CELL_SIZE;

	parent = nullptr;
}

Cell::Cell(int x, int y)
{
    this->x = x;
	this->y = y;
	
	walkable = true;
	isStart = false;
	isEnd = false;
	isInPath = false;

    hCost = 0;
    gCost = 0;

    sdl_rect.x = x * CELL_SIZE;
    sdl_rect.y = y * CELL_SIZE;
    sdl_rect.w = sdl_rect.h = CELL_SIZE;

	parent = nullptr;
}

bool Cell::operator ==(const Cell &cell)
{ 
    if(this->x == cell.x && this->y == cell.y)
        return true;
    return false;
}

bool Cell::operator !=(const Cell &cell)
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

    this->sdl_rect = cell.sdl_rect;
    this->parent = cell.parent;

    return *this;
}

int Cell::fCost()
{
    return gCost + hCost;
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