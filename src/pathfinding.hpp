#pragma once

#include "grid.hpp"
// fix getStart and getEnd methods;
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

    for(auto cell: path)
    {
        if(cell.IsEnd())
            continue;
        cell.setIsInPath();
        grid.moveCell(cell);
    }
}
// mb bug
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

void PathFinding::findPath()
{   
    // Cell start = grid.getStart();
    // Cell end = grid.getEnd();
    Cell start = grid.getCell(9, 14);
    start.setIsStart();
    grid.moveCell(start);
 
    Cell end = grid.getCell(31, 9);
    end.setIsEnd();
    grid.moveCell(end);

    std::vector<Cell> openSet, closedSet;
    openSet.push_back(start);

    while(openSet.size() > 0)
    {
        // sort(openSet.begin(), openSet.end(), [](Cell cell1, Cell cell2){
        //     return(cell1.fCost() <= cell2.fCost() && cell1.getHCost() < cell2.getHCost());
        // });

        Cell cell = openSet.at(0);
        
        // for (int i = 1; i < openSet.size(); i++) 
        // {
        //     if (openSet[i].fCost() < cell.fCost() || openSet[i].fCost() == cell.fCost())
        //     {
        //         if (openSet[i].getHCost() < cell.getHCost())
        //             cell = openSet[i];
        //     }
        // }

        auto itr = openSet.begin() + 1;
        auto cellItr = openSet.begin();
        for(itr; itr != openSet.end(); itr++)
        {
            if((*itr).fCost() <= cell.fCost() && (*itr).getHCost() < cell.fCost())
            {
                cell = *itr;
                cellItr = itr;
            }
        }

        // openSet.erase(openSet.begin());
        openSet.erase(cellItr);
        closedSet.push_back(cell);

        if(cell.IsEnd())
        {
            retracePath(start, end);
            break;
        }

        for(auto neighbour : getNeighbours(cell))
        {
            if(!(neighbour.IsWalkable()) || containsVector(closedSet, neighbour))
                continue;
            
            int newCostToNeighbour = cell.getGCost() + grid.getDistance(cell, neighbour);
            if(newCostToNeighbour < neighbour.getGCost() || !containsVector(openSet, neighbour))
            {
                neighbour.setGCost(newCostToNeighbour);
                neighbour.setHCost(grid.getDistance(neighbour, end));
                neighbour.setParent(cell);
                grid.moveCell(neighbour);
                // grid.moveCell(cell);

                if(!containsVector(openSet, neighbour))
                    openSet.push_back(neighbour);
            }
        }
    }
}
