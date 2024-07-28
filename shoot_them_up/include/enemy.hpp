#pragma once
#include "game_object.hpp"

constexpr int DEFAULT_ENEMY_SPEED = 4;
constexpr short DEFALUT_ENEMY_HEALTH = 1;

class Enemy : public GameObject {
public:
  Enemy();
  Enemy(float x, float y);
  ~Enemy() override;

  void blit(SDL_Renderer *renderer) override;
  void getSize() override;
  void setTexture(SDL_Texture *) override;

  int getEnemySpeed() const;
  bool isDead() const;

  void updatePosition();
  void hitEnemy();

public:
  float dx, dy;

private:
  int speed;
  short health;
};
