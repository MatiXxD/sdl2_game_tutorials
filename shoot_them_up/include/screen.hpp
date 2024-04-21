#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Screen {
public:
    Screen(int, int);
    ~Screen();

    SDL_Renderer* getRenderer() const;
    SDL_Window* getWindow() const;

private:
    SDL_Renderer* renderer;
    SDL_Window* window;

    int width;
    int height;

};