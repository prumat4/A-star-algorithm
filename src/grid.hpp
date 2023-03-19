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
    void setWalkable(int, int);

    Cell* getCell(int, int);
    Cell* getStart();
    Cell* getEnd();

    bool startAndEndExists();
	void clearParents();
    std::vector<Cell*> getNeighbours(Cell*);
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
			if(CellsVector.at(i).IsWalkable())
				CellsVector.at(i).setObstacle();
	}
}

void Grid::setWalkable(int x, int y)
{
	for(int i = 0; i < CellsVector.size(); i++)
	{
		if(CellsVector.at(i).getX() == x && CellsVector.at(i).getY() == y)
            CellsVector.at(i).setWalkable();
	}
}

Cell* Grid::getCell(int x, int y)
{
    for(int i = 0; i < CellsVector.size(); i++) 
    {
        if(CellsVector.at(i).getX() == x && CellsVector.at(i).getY() == y)
            return &CellsVector.at(i);
    }
    
    return &CellsVector.at(CellsVector.size());
}

Cell* Grid::getStart()
{
    int k = 0;
	for(int i = 0; i < CellsVector.size(); i++)
	{
		if(CellsVector.at(i).IsStart())
            return &CellsVector.at(i);
	} 

    return &CellsVector.at(CellsVector.size());
}

Cell* Grid::getEnd()
{
	for(int i = 0; i < CellsVector.size(); i++)
	{
		if(CellsVector.at(i).IsEnd())
            return &CellsVector.at(i);
	}

    return &CellsVector.at(CellsVector.size());
}

bool Grid::startAndEndExists()
{
    int s = 0, e = 0;

    for(auto cell : CellsVector)
    {
        if(cell.IsEnd())
            e++;
        if(cell.IsStart())
            s++;
    }

    if(s == 1 && e == 1)
        return true;
    else return false;
}

void Grid::clearParents()
{
	for(int i = 0; i < CellsVector.size(); i++)
	{
		CellsVector.at(i).clearParent();
	}
}

std::vector<Cell*> Grid::getNeighbours(Cell *cell)
{
    std::vector<Cell*> neighbours;

    for(int i = -1; i <= 1; i++)
    { 
        for(int j = -1; j <= 1; j++)
        {
            if(i == 0 && j == 0)
                continue;
            
            int x = cell->getX() + i;
            int y = cell->getY() + j;

            if(x >= 0 && x < (WINDOW_WIDTH / CELL_SIZE) 
            && y >= 0 && y < (WINDOW_HEIGHT / CELL_SIZE))
            {
				Cell *temporary = getCell(x, y);
					
				if(temporary->IsWalkable())
					neighbours.push_back(temporary);
			}
        }
    }

    return neighbours;
}

int heuristics(Cell *cell1, Cell *cell2)
{
	int x = abs(cell1->getX() - cell2->getX());
	int y = abs(cell1->getY() - cell2->getY());

	if(x > y)
		return 14*y + 10*(x - y);
	
	return 14*x + 10*(y - x);
}

class Path
{
    std::vector<Cell*> path;
public:
    std::vector<Cell*> getPathVector() { return path; }
    
    void pushToPath(Cell *cell) { path.push_back(cell); }
    void clearPath() { path.clear(); }
};

class PathFinding
{
    Grid grid;
    Path path;
    
    void retracePath(Cell *, Cell *);

public:
    Grid& getGrid() { return grid; }
    Path& getPath() { return path; }

    void setStart(int, int);
    void setEnd(int, int);
    void setObstacle(int, int);
    void setWalkable(int, int);
    
    void setPath(std::vector<Cell*>);
    void findPath();
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

void PathFinding::setWalkable(int x, int y)
{
    grid.setWalkable(x, y);
}

void PathFinding::setPath(std::vector<Cell*> vec)
{
    path.clearPath();

    if(vec.size() > 1)
    {
        for(auto cell: vec)
        {
            if((*cell).IsEnd())
                continue;
            path.pushToPath(cell);
        }
    }
}
 
void PathFinding::retracePath(Cell *start, Cell *end)
{
    std::vector<Cell*> vec;
    Cell *current = end;
    
    while(!current->IsStart())
    {
        vec.push_back(grid.getCell(current->getX(), current->getY()));
        current = grid.getCell(current->getParentX(), current->getParentY());
    }

    if(vec.size() > 1)
        setPath(vec);
}

Cell* getLowestFCostHCostCell(const std::vector<Cell*> &cells)
{
    Cell *lowestCostCell = cells.at(0);

    for(auto cell : cells)
    {
        if((*cell).fCost() < lowestCostCell->fCost() || (cell->fCost() == lowestCostCell->fCost() && (cell->getHCost() < (lowestCostCell->getHCost()))))
            lowestCostCell = cell;
    }

    return lowestCostCell;
}

void removeFromVector(std::vector<Cell*> &vec, const Cell *element)
{
    vec.erase(std::remove(vec.begin(), vec.end(), element), vec.end());
}

void getMouseCoordinates(int &x, int &y)
{	
	SDL_GetMouseState(&x, &y);

	int tempX = x % CELL_SIZE;
	int tempY = y % CELL_SIZE;
	
	x -= tempX;
	y -= tempY;
	
	x = x / CELL_SIZE;
	y = y / CELL_SIZE;
}

bool containsVector(std::vector<Cell*> &cells, Cell *cell1)
{
    for(int i = 0; i < cells.size(); i++)
    {
        if(cell1 == cells.at(i))
            return true;    
    }
    return false;
}

void updateNeighbourCell(Cell *current, Cell *neighbour, Cell *end, std::vector<Cell*> &openSet, std::vector<Cell*> &closedSet)
{
    if(!((*neighbour).IsWalkable()) || containsVector(closedSet, neighbour))
        return;

    int newCostToNeighbour = current->getGCost() + heuristics(current, neighbour);
    if(newCostToNeighbour < neighbour->getGCost() || !containsVector(openSet, neighbour))
    {
        neighbour->setGCost(newCostToNeighbour);
        neighbour->setHCost(heuristics(neighbour, end));
        neighbour->setParent(current);

        if(!containsVector(openSet, neighbour))
            openSet.push_back(neighbour);
    }
}

void PathFinding::findPath()
{   
    grid.clearParents();
    
    if(grid.startAndEndExists())
    {
        Cell *start = grid.getStart();
        Cell *end = grid.getEnd();

        bool pathExists = false;
        
        std::vector<Cell*> openSet, closedSet;
        openSet.push_back(start);

        while(openSet.size() > 0)
        {
            Cell *cell = getLowestFCostHCostCell(openSet);
            removeFromVector(openSet, cell);
            closedSet.push_back(cell);

            if(cell->IsEnd())
            {
                retracePath(start, end);
                pathExists = true;
                break;
            }

            for(auto neighbour : grid.getNeighbours(cell))
                updateNeighbourCell(cell, neighbour, end, openSet, closedSet);
        }

        if(!pathExists)
            path.clearPath();
    }
    else 
        path.clearPath();
}