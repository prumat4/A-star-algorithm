#pragma once

#include "menu.hpp"

class Run
{	
	Window window;
    PathFinding pathFinding;

public:
	Grid getGrid() { return pathFinding.getGrid(); }
	
	void run();
};

void Run::run()
{
	SDL_Event sdl_event;   
    bool isRunning = true;
	
	int x, y;
	const Uint8* state = SDL_GetKeyboardState(NULL);

	while(isRunning)
    {	
		while(SDL_PollEvent(&sdl_event) != 0)
		{
			if(sdl_event.type == SDL_QUIT)
				isRunning = false;
			else if(state[SDL_SCANCODE_ESCAPE])
			{
				isRunning = false;
				break;
			}
			else if(state[SDL_SCANCODE_V])
			{
				window.vPressed();
			}
			else if(state[SDL_SCANCODE_C])
			{
				getMouseCoordinates(x, y);
				pathFinding.setObstacle(x, y);
			}
			else if(state[SDL_SCANCODE_X])
			{
				getMouseCoordinates(x, y);
				pathFinding.setWalkable(x, y);
			}
			else if(sdl_event.type == SDL_MOUSEBUTTONDOWN)
			{	
				getMouseCoordinates(x, y);

				if(state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL])
					pathFinding.setStart(x, y);
				else if(state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT])
					pathFinding.setEnd(x,y);
			}
		}

		window.drawGrid(pathFinding);
		// drawGrid(window.getRenderer());
		pathFinding.findPath();
    }
}