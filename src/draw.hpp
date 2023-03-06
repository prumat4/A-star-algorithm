#pragma once

#include "window.hpp"

class Draw
{
    Window window;
    Grid grid;

public:
    void DrawWalkable(SDL_Renderer*, Cell&);
	void DrawObstacle(SDL_Renderer*, Cell&);
	void DrawStart(SDL_Renderer*, Cell&);
	void DrawEnd(SDL_Renderer*, Cell&);
	void DrawPath(SDL_Renderer*, Cell&);

	// void GetMouseCoordinates(int& x, int& y);
    void DrawGrid();
    void Run();
};

// should i move this to other header and thimk about logic 
// void Draw::GetMouseCoordinates(int& x, int& y)
// {	
// 	SDL_GetMouseState(&x, &y);

// 	int tempX = x % CELL_SIZE;
// 	int tempY = y % CELL_SIZE;
	
// 	x -= tempX;
// 	y -= tempY;
	
// 	x = x / CELL_SIZE;
// 	y = y / CELL_SIZE;
// }

void Draw::DrawStart(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 0, 0);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Draw::DrawEnd(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 0);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Draw::DrawObstacle(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Draw::DrawWalkable(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 34, 75, 0);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
}

void Draw::DrawPath(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 0, 0);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Draw::DrawGrid()
{
	for(auto cell : grid.getCellsVector())
	{   
        if(cell.IsWalkable())
            DrawWalkable(window.getRenderer(), cell);
		if(cell.IsStart())
			DrawStart(window.getRenderer(), cell);
		if(cell.IsEnd())
			DrawEnd(window.getRenderer(), cell);
		if(cell.IsInPath())
			DrawPath(window.getRenderer(), cell);
		if(!(cell.IsWalkable()))
			DrawObstacle(window.getRenderer(), cell);
	}
}

void Draw::Run()
{
	SDL_Event sdl_event;   
    bool isRunning = true;

	while(isRunning)
    {	
		// while(SDL_PollEvent(&sdl_event) != 0)
		// {
		// 	if(sdl_event.type == SDL_QUIT)
		// 		isRunning = false;
		// 	else if(sdl_event.type == SDL_KEYDOWN)
		// 	{	// mb refactor this switch statement
		// 		switch(sdl_event.key.keysym.sym)
		// 		{
		// 			case SDLK_ESCAPE:
		// 				isRunning = false;
		// 				break;
		// 		}
		// 	}
		// 	else if(sdl_event.type == SDL_MOUSEBUTTONDOWN)
		// 	{	
		// 		int x, y;
		// 		GetMouseCoordinates(x, y);

		// 		const Uint8* state = SDL_GetKeyboardState(NULL);
				
		// 		if(state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL])
		// 		{
		// 			SetStartCell(x, y);
		// 		}
		// 		else if(state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT])
		// 		{
		// 			SetEndCell(x,y);
		// 		}
		// 		else
		// 			SetObstacleCell(x, y);
		// 	}
		// }
		SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
		SDL_RenderClear(window.getRenderer());

        DrawGrid();

		SDL_RenderPresent(window.getRenderer());
    }
}