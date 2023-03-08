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

    bool containsVector(std::vector<Cell>, Cell&);

    void findPath();
    void retracePath(Cell&, Cell&);
    Cell getLowestFCostHCostCell(const std::vector<Cell>&);
    void updateNeighbourCell(Cell&, Cell&, Cell& end, std::vector<Cell>&, std::vector<Cell>&);
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

    if(neighbours.size() == 0)
        clearPath();
        
    return neighbours;
}

void PathFinding::clearPath()
{
    for(auto cell: grid.getCellsVector())
    {
        if(cell.IsInPath())
        {
            cell.setWalkable();
            grid.moveCell(cell);
        }
    }
}

void PathFinding::setPath(std::vector<Cell> path)
{
    clearPath();
    if(path.size() > 1)
    {
        for(auto cell: path)
        {
            if(cell.IsEnd())
                continue;
            cell.setIsInPath();
            grid.moveCell(cell);
        }
    }
}

bool PathFinding::containsVector(std::vector<Cell> cells, Cell& cell1)
{
    for(int i = 0; i < cells.size(); i++)
    {
        if(cell1 == cells.at(i))
            return true;
    }

    return false;
}
    
void PathFinding::retracePath(Cell& start, Cell& end)
{
    std::vector<Cell> path;
    Cell current = end;
    
    while(!current.IsStart())
    {
        path.push_back(grid.getCell(current.getX(), current.getY()));
        current = grid.getCell(current.getParentX(), current.getParentY());
    }
    setPath(path);
}

Cell PathFinding::getLowestFCostHCostCell(const std::vector<Cell>& cells)
{
    Cell lowestCostCell = cells.at(0);

    for(auto cell : cells)
    {
        if(cell.fCost() < lowestCostCell.fCost() || (cell.fCost() == lowestCostCell.fCost() && cell.getHCost() < lowestCostCell.getHCost()))
        {
            lowestCostCell = cell;
        }
    }

    return lowestCostCell;
}

void PathFinding::updateNeighbourCell(Cell& current, Cell& neighbour, Cell& end, std::vector<Cell>& openSet, std::vector<Cell>& closedSet)
{
    if(!(neighbour.IsWalkable()) || containsVector(closedSet, neighbour))
        return;

    int newCostToNeighbour = current.getGCost() + grid.getDistance(current, neighbour);
    if(newCostToNeighbour < neighbour.getGCost() || !containsVector(openSet, neighbour))
    {
        neighbour.setGCost(newCostToNeighbour);
        neighbour.setHCost(grid.getDistance(neighbour, end));
        neighbour.setParent(current);
        grid.moveCell(neighbour);

        if(!containsVector(openSet, neighbour))
            openSet.push_back(neighbour);
    }
}

void removeFromVector(std::vector<Cell>& vec, const Cell& element)
{
    vec.erase(std::remove(vec.begin(), vec.end(), element), vec.end());
}

void PathFinding::findPath()
{   
    grid.clearParents();
    Cell start, end;
    grid.getStart(start);
    grid.getEnd(end);

    if(grid.pathExists())
    {
        std::vector<Cell> openSet, closedSet;
        openSet.push_back(start);

        while(openSet.size() > 0)
        {
            Cell cell = getLowestFCostHCostCell(openSet);
            removeFromVector(openSet, cell);
            closedSet.push_back(cell);

            if(cell.IsEnd())
            {
                retracePath(start, end);
                break;
            }

            for(auto neighbour : getNeighbours(cell))
                updateNeighbourCell(cell, neighbour, end, openSet, closedSet);
        }

    }
    else
        clearPath();
}