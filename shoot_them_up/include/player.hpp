#pragma once
#include <string>
#include "game_object.hpp"


constexpr int DEFAULT_PLAYER_SPEED = 8;
constexpr int DEFAULT_PLAYER_RELOAD = 16;
constexpr short DEFAULT_PLAYER_HEALTH = 3;


class Player : public GameObject {
public:
  Player();
  Player(float x, float y);
  ~Player() override;

  void blit(SDL_Renderer *renderer) override;
  void getSize() override;
  void setTexture(SDL_Texture*) override;

  int getPlayerSpeed() const;

  void updatePosition();
  void reloadTick(); 
  void startShoot(bool);
  
  bool isShoot() const;
  bool isReload() const; 

public:
  float dx, dy;

private:
  int speed;
  int reload; 
  short health;
  bool shoot;
};
