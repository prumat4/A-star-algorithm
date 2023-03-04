#pragma once

#include "window.hpp"

class Draw
{
public:
    Window window;
    Grid grid;

    void DrawWalkable(SDL_Renderer*, Cell&);

    void DrawGrid();
    void Run();
};

// Draw::Draw()
// {
//     window;
//     grid;
// }

void Draw::DrawWalkable(SDL_Renderer* sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 34, 75, 0);
	SDL_RenderDrawRect(sdl_renderer, &cell.sdl_rect);
}

void Draw::DrawGrid()
{
	SDL_SetRenderDrawColor(window.sdl_renderer, 34, 34, 34, 34);
	for(auto cell : grid.CellsVector)
	{   
        if(cell.walkable)
            DrawWalkable(window.sdl_renderer, cell);
		// if(cell.isStart)
		// 	cell.DrawStart(sdl_renderer);
		// if(cell.isEnd)
		// 	cell.DrawEnd(sdl_renderer);
		// if(cell.isInPath)
		// 	cell.DrawPathCell(sdl_renderer);
		// if(cell.walkable)
		// 	cell.DrawWalkable(sdl_renderer);
		// if(!(cell.Walkable))
		// 	cell.DrawObstacle(sdl_renderer);
	}

}

void Draw::Run()
{   
    bool isRunning = true;

	while(isRunning)
    {
        DrawGrid();
    }
}