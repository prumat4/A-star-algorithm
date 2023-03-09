#pragma once

#include "grid.hpp"

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


class Draw
{
    Cell cell;
public:
	Draw() = default;
	Draw(Cell);
    
	void drawWalkable(SDL_Renderer*);
	void drawObstacle(SDL_Renderer*);
	void drawStart(SDL_Renderer*);
	void drawEnd(SDL_Renderer*);
	void drawPath(SDL_Renderer*);

    void drawCell(SDL_Renderer*);
};

Draw::Draw(Cell cell)
{
	this->cell = cell;
}

void Draw::drawStart(SDL_Renderer *sdl_renderer)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 100, 255, 255);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Draw::drawEnd(SDL_Renderer *sdl_renderer)
{
	SDL_SetRenderDrawColor(sdl_renderer, 220, 0, 255, 255);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Draw::drawPath(SDL_Renderer *sdl_renderer)
{	
	SDL_SetRenderDrawColor(sdl_renderer, 227, 255, 255, 255);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Draw::drawObstacle(SDL_Renderer *sdl_renderer)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Draw::drawWalkable(SDL_Renderer *sdl_renderer)
{	
	SDL_SetRenderDrawColor(sdl_renderer, 116, 111, 117, 255);
	SDL_Rect rect = cell.getRect();
	SDL_RenderDrawRect(sdl_renderer, &rect);
}


void Draw::drawCell(SDL_Renderer* sdl_renderer)
{	
	if(cell.IsStart())
		drawStart(sdl_renderer);
	if(cell.IsInPath())
		drawPath(sdl_renderer);
	if(cell.IsEnd())
		drawEnd(sdl_renderer);
	if(cell.IsWalkable())
        drawWalkable(sdl_renderer);
	if(!(cell.IsWalkable()))
		drawObstacle(sdl_renderer);
}

class Run
{
	Window window;
	PathFinding grid;
	Draw draw;
public:
	void run();
};

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

		SDL_SetRenderDrawColor(window.getRenderer(), 81, 81, 81, 255);
		SDL_RenderClear(window.getRenderer());
		
        for(auto cell: grid.getGrid().getCellsVector())
		{	
			Draw temp(cell);
			draw = temp;
			temp.drawCell(window.getRenderer());
		}

		grid.findPath();
			
		SDL_RenderPresent(window.getRenderer());
    }
}