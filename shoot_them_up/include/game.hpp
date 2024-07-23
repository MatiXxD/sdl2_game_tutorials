#pragma once

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

#include "color.hpp"
#include "exception.hpp"
#include "screen.hpp"

#include "game_object.hpp"
#include "bullet.hpp"
#include "player.hpp"


constexpr int DEFAULT_SCREEN_WIDTH = 600;
constexpr int DEFAULT_SCREEN_HEIGHT = 900;
constexpr char PLAYER_TEXTURE[] = "player";
constexpr char PLAYER_TEXTURE_PATH[] = "/textures/player.png";
constexpr char BULLET_TEXTURE[] = "bullet";
constexpr char BULLET_TEXTURE_PATH[] = "/textures/bullet.png";


class Game {
public:
  enum class status { QUIT, CONTINUE };
  
  Game();
  Game(int, int);
  Game(int, int, position);
  ~Game();

  int inputHandle();
  int handleKeydown(SDL_KeyboardEvent *);
  int handleKeyup(SDL_KeyboardEvent *);
  
  void updateState();
  void updatePlayer();
  void updateBullets();

  void fireBullet();

  void prepareScene(const color &) const;
  void presentScene() const;

  void setPlayer(int, int);
  void loadTexture(const std::string&, const std::string&, SDL_Renderer*);
  void loadTextures(const std::string &);
  void drawAll() const;

  Player *getPlayer();
  Screen *getScreen();

private:
  void initKeymap();

private:
  int screenWidth, screenHeight;
  Screen *screen;
  Player *player;

  std::list<Bullet*> bullets; 
  
  std::unordered_map<std::string, SDL_Texture*> textures;
  std::unordered_map<int, bool> keymap;
};
