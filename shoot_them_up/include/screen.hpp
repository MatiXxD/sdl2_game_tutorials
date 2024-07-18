#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <utility>

class Screen {
public:
  Screen(int, int);
  ~Screen();

  SDL_Renderer *getRenderer() const;
  SDL_Window *getWindow() const;
  std::pair<int, int> getSize() const;

private:
  SDL_Renderer *renderer;
  SDL_Window *window;

  int width;
  int height;
};
