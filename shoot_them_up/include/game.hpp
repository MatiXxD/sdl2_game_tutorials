#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "color.hpp"
#include "exception.hpp"
#include "screen.hpp"

#include "bullet.hpp"
#include "player.hpp"

class Game {
public:
  enum class status { QUIT, CONTINUE };

  Game(int, int);
  Game(int, int, position);
  ~Game();

  int inputHandle();
  int handleKeydown(SDL_KeyboardEvent *);
  int handleKeyup(SDL_KeyboardEvent *);
  void updateState();

  void prepareScene(const color &) const;
  void presentScene() const;

  void setPlayer(int, int);
  void loadTextures(const std::string &);
  void drawAll() const;

  Player *getPlayer();
  Screen *getScreen();

private:
  Screen *screen;
  Player *player;
  Bullet *bullet;
};
