#pragma once

#include "maze.hpp"

class Window
{
    SDL_Window *sdl_window { nullptr };
    SDL_Renderer *sdl_renderer { nullptr };
public:

    SDL_Window* getWindow() { return sdl_window; }
    SDL_Renderer* getRenderer() { return sdl_renderer; }

    Window();
    ~Window();
};

Window::Window()
{   
    sdl_window = SDL_CreateWindow(
        "A-star-algorithm",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

    if(sdl_window == nullptr)
    {
		printf("Could not create window: %s", SDL_GetError());
    }
}

Window::~Window()
{
    if(sdl_renderer)
        SDL_DestroyRenderer(sdl_renderer);
    
    if(sdl_window)
        SDL_DestroyWindow(sdl_window);
}


class Run
{	
	Window window;
    PathFinding pathFinding;

	void drawWalkable(SDL_Renderer*, Cell&);
	void drawObstacle(SDL_Renderer*, Cell&);
	void drawStart(SDL_Renderer*, Cell&);
	void drawEnd(SDL_Renderer*, Cell&);
	void drawPath(SDL_Renderer*);

	void vPressed();

public:
	Grid getGrid() { return pathFinding.getGrid(); }
	
	void run();
    void drawGrid(SDL_Renderer*);
};

void Run::vPressed()
{	
	Uint32 flags = SDL_GetWindowFlags(window.getWindow());
    if(flags & SDL_WINDOW_FULLSCREEN)
        SDL_SetWindowFullscreen(window.getWindow(), 0);
    else
        SDL_SetWindowFullscreen(window.getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void Run::drawStart(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 80, 255, 255);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Run::drawEnd(SDL_Renderer *sdl_renderer, Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 220, 0, 255, 255);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Run::drawPath(SDL_Renderer *sdl_renderer)
{	
	auto path = pathFinding.getPath().getPathVector();
	
	if(path.size())
	{
		int redCoef = 220 / path.size();
		int greenCoef = 80 / path.size();

		for(int i = 0; i < path.size(); i++)
		{
			SDL_Rect rect = path.at(i).getRect();
			SDL_SetRenderDrawColor(sdl_renderer, (path.size() - i) * redCoef, i * greenCoef, 255, 255);
			SDL_RenderDrawRect(sdl_renderer, &rect);
			SDL_RenderFillRect(sdl_renderer, &rect);
		}
	}
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
	SDL_SetRenderDrawColor(sdl_renderer, 116, 111, 117, 255);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
}

void Run::drawGrid(SDL_Renderer* sdl_renderer)
{	
	SDL_SetRenderDrawColor(window.getRenderer(), 81, 81, 81, 255);
	SDL_RenderClear(window.getRenderer());
	
	auto myGrid = pathFinding.getGrid().getCellsVector();
	for(auto cell : myGrid)
	{
		if(cell.IsStart())
			drawStart(sdl_renderer, cell);
		if(cell.IsEnd())
			drawEnd(sdl_renderer, cell);
		if(cell.IsWalkable())
			drawWalkable(sdl_renderer, cell);
		if(!(cell.IsWalkable()))
			drawObstacle(sdl_renderer, cell);
	}
	
	drawPath(sdl_renderer);
	SDL_RenderPresent(window.getRenderer());
}

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
				vPressed();
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
				// refactor 
				getMouseCoordinates(x, y);

				if(state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL])
					pathFinding.setStart(x, y);
				else if(state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT])
					pathFinding.setEnd(x,y);
			}
		}
		
		drawGrid(window.getRenderer());
		pathFinding.findPath();
    }
}