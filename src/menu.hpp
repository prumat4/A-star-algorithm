#pragma once

#include "grid.hpp"

class Button 
{
    int buttonWidth;
    int buttonHeight;

    int x;
    int y;

    SDL_Rect rectangle;

    void updateRect();
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setWidth(int width) { buttonWidth = width; }
    void setHeight(int height) { buttonHeight = height; }

public:
    void set(int, int, int, int);
    SDL_Rect getRect() { return rectangle; }    

    Button();
};

void Button::updateRect()
{
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = buttonWidth;
    rectangle.h = buttonHeight; 
}

void Button::set(int x, int y, int widht, int height)
{
    setX(x);
    setY(y);
    setWidth(widht);
    setHeight(height);

    updateRect();
}

Button::Button()
{
    x = 0;
    y = 0;

    buttonHeight = 0;
    buttonWidth = 0;

    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = buttonWidth;
    rectangle.h = buttonHeight;
}

class Menu
{
    Button runAlgorithm;
    Button runMaze;
    Button exit;

public: 
    Menu();

    Button& getRunAlgorithmButton() { return runAlgorithm; }
    Button& getRunMazeButton() { return runMaze; }
    Button& getExitButton() { return exit; }
};

Menu::Menu()
{
    runAlgorithm.set(700, 200, 520, 120);
    runMaze.set(700, 400, 520, 120);
    exit.set(700, 700, 520, 120);
}

class Window
{
    SDL_Window *sdl_window { nullptr };
    SDL_Renderer *sdl_renderer { nullptr };
	Menu menu;
	
    void drawRect(SDL_Rect &);

	void drawWalkable(Cell&);
	void drawObstacle(Cell&);
	void drawStart(Cell&);
	void drawEnd(Cell&);
	void drawPath(Path &);

    void drawButton(Button &);

public:
    SDL_Window* getWindow() { return sdl_window; }
    SDL_Renderer* getRenderer() { return sdl_renderer; }

	void vPressed();

    void drawGrid(PathFinding pathFinding);
    void drawMenu(); 

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

void Window::vPressed()
{	
	Uint32 flags = SDL_GetWindowFlags(getWindow());
    if(flags & SDL_WINDOW_FULLSCREEN)
        SDL_SetWindowFullscreen(getWindow(), 0);
    else
        SDL_SetWindowFullscreen(getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void Window::drawRect(SDL_Rect &rect)
{
	SDL_RenderDrawRect(sdl_renderer, &rect);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void Window::drawStart(Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 80, 255, 255);
	drawRect(cell.getRect());
    SDL_SetRenderDrawColor(sdl_renderer, 0, 100, 255, 0);
}

void Window::drawEnd(Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 220, 0, 255, 255);
	drawRect(cell.getRect());
}

void Window::drawObstacle(Cell& cell)
{
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0);
	drawRect(cell.getRect());
	SDL_SetRenderDrawColor(sdl_renderer, 20, 20, 20, 0);
    SDL_Rect rect = cell.getRect();
    
    rect.x += 10;
    rect.y += 10;
    rect.w = 14;
    rect.h = 14;
	SDL_RenderDrawRect(sdl_renderer, &rect);
    SDL_RenderFillRect(sdl_renderer, &rect);
}

void Window::drawWalkable(Cell& cell)
{	
	SDL_SetRenderDrawColor(sdl_renderer, 116, 111, 117, 255);
	SDL_RenderDrawRect(sdl_renderer, &cell.getRect());
}

void Window::drawPath(Path &path)
{	
    auto _path = path.getPathVector();
	if(_path.size() > 0)
	{
		int redCoef = 220 / _path.size();
		int greenCoef = 80 / _path.size();

		for(int i = 0; i < _path.size(); i++)
		{
			SDL_Rect rect = (*_path.at(i)).getRect();
			SDL_SetRenderDrawColor(sdl_renderer, (_path.size() - i) * redCoef, i * greenCoef, 255, 255);
			SDL_RenderDrawRect(sdl_renderer, &rect);
			SDL_RenderFillRect(sdl_renderer, &rect);
		}
	}
}

void Window::drawGrid(PathFinding pathFinding)
{	
	SDL_SetRenderDrawColor(sdl_renderer, 81, 81, 81, 255);
	SDL_RenderClear(sdl_renderer);
	
	drawPath(pathFinding.getPath());

	auto myGrid = pathFinding.getGrid().getCellsVector();
	for(auto cell : myGrid)
	{
		if(cell.IsStart())
			drawStart(cell);
		if(cell.IsEnd())
			drawEnd(cell);
		if(cell.IsWalkable())
			drawWalkable(cell);
		if(!(cell.IsWalkable()))
			drawObstacle(cell);
	}

    drawMenu();

	SDL_RenderPresent(sdl_renderer);
}

void Window::drawButton(Button &button)
{
    SDL_Rect rect = button.getRect();
	SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 0);
    SDL_RenderDrawRect(sdl_renderer, &rect);
    SDL_RenderFillRect(sdl_renderer, &rect);
}

void Window::drawMenu()
{   
    drawButton(menu.getRunAlgorithmButton());
    drawButton(menu.getRunMazeButton());
    drawButton(menu.getExitButton());

    // SDL_Surface * image = SDL_LoadBMP("../images/1.bmp");
    // SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer, image);
    // SDL_RenderCopy(sdl_renderer, texture, NULL, NULL);
}