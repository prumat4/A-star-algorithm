#pragma once

#include "menu.hpp"

bool runAlgorithmAimed(int &x, int &y)
{
	SDL_GetMouseState(&x, &y);
	return x >= RUN_ALGORITHM_X_POS 
		&& x <= RUN_ALGORITHM_X_POS + RUN_ALGORITHM_WIDTH 
		&& y >= RUN_ALGORITHM_Y_POS 
		&& y <= RUN_ALGORITHM_Y_POS + RUN_ALGORITHM_HEIGHT;
}

bool runInstructionAimed(int &x, int &y)
{
	SDL_GetMouseState(&x, &y);

	return x >= RUN_INSTRUCTION_X_POS 
		&& x <= RUN_INSTRUCTION_X_POS + RUN_INSTRUCTION_WIDTH 
		&& y >= RUN_INSTRUCTION_Y_POS 
		&& y <= RUN_INSTRUCTION_Y_POS + RUN_INSTRUCTION_HEIGHT;
}

bool exitAimed(int &x ,int &y)
{
	SDL_GetMouseState(&x, &y);

	return x >= EXIT_X_POS 
		&& x <= EXIT_X_POS + EXIT_WIDTH 
		&& y >= EXIT_Y_POS 
		&& y <= EXIT_Y_POS + EXIT_HEIGHT;
}

bool mouseButtonClicked(SDL_Event &sdl_event)
{
	return sdl_event.type == SDL_MOUSEBUTTONDOWN;
}

class Run
{	
	Window window;
    PathFinding pathFinding;

	void handleAStarAiming(int &, int &);
	void handleInstructionAiming(int &, int &);
	void handleExitAiming(int &, int&);
	
public:
	Grid getGrid() { return pathFinding.getGrid(); }
	
	void handleAiming(int &x, int& y);

	void runAStar(bool &);
	void runInstruction(bool &);
	void run();
};

void Run::handleAStarAiming(int &x, int &y)
{
	if(runAlgorithmAimed(x, y))
		window.aStarAimed(true);
	if(!runAlgorithmAimed(x, y))
		window.aStarAimed(false);
}

void Run::handleInstructionAiming(int &x, int&y)
{
	if(runInstructionAimed(x,y))
		window.instructionAimed(true);
	if(!runInstructionAimed(x,y))
		window.instructionAimed(false);
}

void Run::handleExitAiming(int &x, int &y)
{
	if(exitAimed(x,y))
		window.exitAimed(true);
	if(!exitAimed(x,y))
		window.exitAimed(false);
}

void Run::handleAiming(int &x, int &y)
{
	handleAStarAiming(x, y);
	handleInstructionAiming(x, y);
	handleExitAiming(x , y);
}

void Run::runInstruction(bool &running)
{
	bool isRunning = true;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	SDL_Event sdl_event;
	while(isRunning)
	{
		window.drawInstruction();
		while(SDL_PollEvent(&sdl_event) != 0)
		{
			if(sdl_event.type == SDL_QUIT)
			{
				isRunning = false;
				running = false;
				SDL_RenderClear(window.getRenderer());
				break;
			}
			if(state[SDL_SCANCODE_ESCAPE])
			{
				isRunning = false;
				SDL_RenderClear(window.getRenderer());
				break;
			}
		}
	}
}

void Run::runAStar(bool &running)
{
	bool isRunning = true;
	int x , y;
	SDL_Event sdl_event;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	while(isRunning)
	{
		while(SDL_PollEvent(&sdl_event) != 0)
		{
			getMouseCoordinates(x, y);
			if(state[SDL_SCANCODE_ESCAPE])
			{
				isRunning = false;
				SDL_RenderClear(window.getRenderer());
				break;
			}	
			if(sdl_event.type == SDL_QUIT)
			{
				isRunning = false;
				running = false;
				SDL_RenderClear(window.getRenderer());
				break;
			}
			if(state[SDL_SCANCODE_C])
				pathFinding.setObstacle(x,y );
			if(state[SDL_SCANCODE_X])
				pathFinding.setWalkable(x,y );
			if(sdl_event.type == SDL_MOUSEBUTTONDOWN)
			{
				if(state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL])
					pathFinding.setStart(x, y);
				if(state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT])
					pathFinding.setEnd(x, y);
			}
		}
			
		window.drawGrid(pathFinding);
		pathFinding.findPath();
	}
}

void Run::run()
{
	SDL_Event sdl_event;   
    bool running = true, menuRunning = true;
	
	int x, y;

	while(running)
    {	
		while(SDL_PollEvent(&sdl_event) != 0)
		{	
			if(menuRunning)
				window.drawMenu();
			handleAiming(x, y);
			if(mouseButtonClicked(sdl_event))
			{
				if(runAlgorithmAimed(x, y))
					runAStar(running);
				if(runInstructionAimed(x ,y))
					runInstruction(running);
				if(exitAimed(x ,y))
				{
					running = false;
					SDL_RenderClear(window.getRenderer());
				}
			}
			if(sdl_event.type == SDL_QUIT)
			{
				running = false;
				SDL_RenderClear(window.getRenderer());
			}
		}
    }
}