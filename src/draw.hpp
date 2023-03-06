#pragma once

#include "window.hpp"

class Run
{
    Window window;
    PathFinding grid;

public:
    void drawWalkable(SDL_Renderer*, Cell&);
	void drawObstacle(SDL_Renderer*, Cell&);
	void drawStart(SDL_Renderer*, Cell&);
	void drawEnd(SDL_Renderer*, Cell&);
	void drawPath(SDL_Renderer*, Cell&);

    void drawGrid();
    void run();
};

void Run::drawStart(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 0, 0);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Run::drawEnd(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 0);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Run::drawObstacle(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Run::drawWalkable(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 34, 75, 0);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
}

void Run::drawPath(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 0, 0);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Run::drawGrid()
{	
	auto myGrid = grid.getGrid();
	for(auto cell : myGrid.getCellsVector())
	{   
        if(cell.IsWalkable())
            drawWalkable(window.getRenderer(), cell);
		if(cell.IsStart())
			drawStart(window.getRenderer(), cell);
		if(cell.IsEnd())
			drawEnd(window.getRenderer(), cell);
		if(cell.IsInPath())
			drawPath(window.getRenderer(), cell);
		if(!(cell.IsWalkable()))
			drawObstacle(window.getRenderer(), cell);
	}
}

void Run::run()
{
	SDL_Event sdl_event;   
    bool isRunning = true;

	while(isRunning)
    {	
		while(SDL_PollEvent(&sdl_event) != 0)
		{
			if(sdl_event.type == SDL_QUIT)
				isRunning = false;
			else if(sdl_event.type == SDL_KEYDOWN)
			{	// refactor
				switch(sdl_event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						isRunning = false;
						break;
				}
			}
			else if(sdl_event.type == SDL_MOUSEBUTTONDOWN)
			{	
				int x, y;
				grid.getMouseCoordinates(x, y);

				const Uint8* state = SDL_GetKeyboardState(NULL);
				// refactor 
				if(state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL])
					grid.setStart(x, y);
				else if(state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT])
					grid.setEnd(x,y);
				else
					grid.setObstacle(x, y);
			}
		}
		SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
		SDL_RenderClear(window.getRenderer());

        drawGrid();
		Cell cell = grid.getGrid().getStart();
		grid.getNeighbours(cell);
		SDL_RenderPresent(window.getRenderer());
    }
}