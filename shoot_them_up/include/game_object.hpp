#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

struct position {
  float x;
  float y;

  position() : x(0), y(0) {}
  position(float x, float y) : x(x), y(y) {}
};

class GameObject {
public:
  GameObject() : pos(position(0, 0)), texture(nullptr) {}
  GameObject(float x, float y) : pos(position(x, y)), texture(nullptr) {}
  virtual ~GameObject() {}

  virtual void blit(SDL_Renderer *renderer) = 0;
  virtual void getSize() = 0;
  virtual void setTexture(SDL_Texture *) = 0;

  SDL_Texture *getTexture() { return texture; }
  position getPosition() const { return pos; }
  position &getPosition() { return pos; }

public:
  position pos;
  int h, w;

protected:
  SDL_Texture *texture;
};
