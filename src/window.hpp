#pragma once

#include "grid.hpp"

class Window
{
public:
    SDL_Window *sdl_window { nullptr };
    SDL_Renderer *sdl_renderer { nullptr };

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