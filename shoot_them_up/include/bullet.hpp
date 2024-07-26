#pragma once
#include "game_object.hpp"
#include <SDL_render.h>
#include <string>

constexpr int DEFAULT_BULLET_SPEED_X = 0;
constexpr int DEFAULT_BULLET_SPEED_Y = -12;
constexpr short DEFAULT_BULLET_HEALTH = 1;

class Bullet : public GameObject {
public:
  Bullet();
  Bullet(float x, float y);
  ~Bullet() override;

  void blit(SDL_Renderer *renderer) override;
  void getSize() override;
  void setTexture(SDL_Texture *) override;

  void updatePosition();

public:
  float dx, dy;

private:
  short health;
};
