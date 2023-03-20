#pragma once

#include "grid.hpp"

#define RUN_ALGORITHM_X_POS 700
#define RUN_ALGORITHM_Y_POS 200
#define RUN_ALGORITHM_WIDTH 520
#define RUN_ALGORITHM_HEIGHT 120

#define RUN_INSTRUCTION_X_POS 700
#define RUN_INSTRUCTION_Y_POS 400
#define RUN_INSTRUCTION_WIDTH 520
#define RUN_INSTRUCTION_HEIGHT 120

#define EXIT_X_POS 700 
#define EXIT_Y_POS 700
#define EXIT_WIDTH 520
#define EXIT_HEIGHT 120

class Button 
{
    int buttonWidth;
    int buttonHeight;

    int x;
    int y;
    
    bool isAimed { false };

    SDL_Surface *sdl_image;
    SDL_Texture *sdl_texture;

    void updateRect(SDL_Rect &rect);
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setWidth(int width) { buttonWidth = width; }
    void setHeight(int height) { buttonHeight = height; }

public:

    Button& operator =(const Button &button);
    void set(int, int, int, int);
    
    bool IsAimed() { return isAimed; }

    void changeAimedStatus(bool var) { isAimed = var; }

    SDL_Texture* getTexture() { return sdl_texture; }
    SDL_Surface* getSurface() { return sdl_image; }
    
    void setSurface(SDL_Surface *surface) { this->sdl_image = surface; }
    void setTexture(SDL_Texture *texture) { this->sdl_texture = texture; }

    Button();
};

Button &Button::operator=(const Button &button)
{
    this->x = button.x;
    this->y = button.y;

    this->buttonHeight = button.buttonHeight;
    this->buttonWidth = button.buttonWidth;
    
    this->sdl_image = button.sdl_image;
    this->sdl_texture = button.sdl_texture;
    this->isAimed = button.isAimed;

    return *this;
}

void Button::updateRect(SDL_Rect &rect)
{
    rect.x = x;
    rect.y = y;
    rect.w = buttonWidth;
    rect.h = buttonHeight; 
}

void Button::set(int x, int y, int widht, int height)
{
    setX(x);
    setY(y);
    setWidth(widht);
    setHeight(height);
}

Button::Button()
{
    x = 0;
    y = 0;

    buttonHeight = 0;
    buttonWidth = 0;
}

class Menu
{
    Button aStarButton;
    Button instructionButton;
    Button exitButton;

public: 
    Menu();

    Button& getRunAlgorithmButton() { return aStarButton; }
    Button& getInstructionButton() { return instructionButton; }
    Button& getExitButton() { return exitButton; }

    void aStarAimed(bool var) { aStarButton.changeAimedStatus(var); }
    void instructionAimed(bool var) { instructionButton.changeAimedStatus(var); }
    void exitAimed(bool var) { exitButton.changeAimedStatus(var); }
};

Menu::Menu()
{
    aStarButton.set(
        RUN_ALGORITHM_X_POS, 
        RUN_ALGORITHM_Y_POS, 
        RUN_ALGORITHM_WIDTH, 
        RUN_ALGORITHM_HEIGHT);

    instructionButton.set(
        RUN_INSTRUCTION_X_POS, 
        RUN_INSTRUCTION_Y_POS, 
        RUN_INSTRUCTION_WIDTH, 
        RUN_INSTRUCTION_HEIGHT);

    exitButton.set(
        EXIT_X_POS, 
        EXIT_Y_POS, 
        EXIT_WIDTH, 
        EXIT_HEIGHT);
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

    void drawAStarButton();
    void drawInstructionButton();
    void drawExitButton();
public:
    SDL_Window* getWindow() { return sdl_window; }
    SDL_Renderer* getRenderer() { return sdl_renderer; }

    void drawGrid(PathFinding pathFinding);
    void drawMenu(); 
    void drawInstruction();

    void aStarAimed(bool var) { menu.aStarAimed(var); }
    void instructionAimed(bool var) { menu.instructionAimed(var); }
    void exitAimed(bool var) { menu.exitAimed(var); }

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
    SDL_RenderClear(sdl_renderer);

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
	SDL_RenderPresent(sdl_renderer);
}

void Window::drawAStarButton()
{
    auto button = menu.getRunAlgorithmButton();
    
    if(button.IsAimed())
        button.setSurface(SDL_LoadBMP("../images/a-star-button-pressed.bmp"));
    else 
        button.setSurface(SDL_LoadBMP("../images/a-star-button.bmp"));

    button.setTexture(SDL_CreateTextureFromSurface(sdl_renderer, button.getSurface()));
    SDL_Rect dstrect = { RUN_ALGORITHM_X_POS, RUN_ALGORITHM_Y_POS, RUN_ALGORITHM_WIDTH, RUN_ALGORITHM_HEIGHT };
    SDL_RenderCopy(sdl_renderer, button.getTexture(), NULL, &dstrect);
}

void Window::drawInstructionButton()
{
    auto button = menu.getInstructionButton();
    
    if(button.IsAimed())
        button.setSurface(SDL_LoadBMP("../images/instruction-button-pressed.bmp"));
    else
        button.setSurface(SDL_LoadBMP("../images/instruction-button.bmp"));
    
    button.setTexture(SDL_CreateTextureFromSurface(sdl_renderer, button.getSurface()));
    SDL_Rect dstrect = { RUN_INSTRUCTION_X_POS, RUN_INSTRUCTION_Y_POS, RUN_INSTRUCTION_WIDTH, RUN_INSTRUCTION_HEIGHT };
    SDL_RenderCopy(sdl_renderer, button.getTexture(), NULL, &dstrect);
}

void Window::drawExitButton()
{
    auto button = menu.getExitButton();

    if(button.IsAimed())
        button.setSurface(SDL_LoadBMP("../images/exit-button-pressed.bmp"));
    else
        button.setSurface(SDL_LoadBMP("../images/exit-button.bmp"));
        
    button.setTexture(SDL_CreateTextureFromSurface(sdl_renderer, button.getSurface()));
    SDL_Rect dstrect = { EXIT_X_POS, EXIT_Y_POS, EXIT_WIDTH, EXIT_HEIGHT };
    SDL_RenderCopy(sdl_renderer, button.getTexture(), NULL, &dstrect);
}

void Window::drawMenu()
{   
    SDL_RenderClear(sdl_renderer);
	SDL_SetRenderDrawColor(sdl_renderer, 151, 151, 151, 255);

    drawAStarButton();
    drawInstructionButton();
    drawExitButton();
    
    SDL_RenderPresent(sdl_renderer);
}

void Window::drawInstruction()
{
    SDL_RenderClear(sdl_renderer);

    SDL_Surface *image = SDL_LoadBMP("../images/instruction.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, image);

    SDL_RenderCopy(sdl_renderer, texture, NULL, NULL);
    SDL_RenderPresent(sdl_renderer);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}