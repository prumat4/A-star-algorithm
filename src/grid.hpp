#pragma once

#include "cell.hpp"

class Grid
{
    std::vector<Cell> CellsVector;
public:
    Grid();
    auto getCellsVector() { return CellsVector; }
    
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