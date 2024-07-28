#pragma once

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

#include "color.hpp"
#include "game_utility.hpp"
#include "exception.hpp"
#include "screen.hpp"

#include "bullet.hpp"
#include "game_object.hpp"
#include "player.hpp"
#include "enemy.hpp"

constexpr int DEFAULT_SCREEN_WIDTH = 600;
constexpr int DEFAULT_SCREEN_HEIGHT = 900;
constexpr int DEFAULT_ENEMY_SPAWN_TIME = 30;
constexpr char PLAYER_TEXTURE[] = "player";
constexpr char PLAYER_TEXTURE_PATH[] = "/textures/player.png";
constexpr char BULLET_TEXTURE[] = "bullet";
constexpr char BULLET_TEXTURE_PATH[] = "/textures/bullet.png";
constexpr char ENEMY_TEXTURE[] = "enemy";
constexpr char ENEMY_TEXTURE_PATH[] = "/textures/enemy.png";



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
  void updateEnemies();
  void spawnEnemies();

  void fireBullet();
  bool bulletHitEnemy(Bullet*);

  void prepareScene(const color &) const;
  void presentScene() const;

  void setPlayer(int, int);
  void loadTexture(const std::string &, const std::string &, SDL_Renderer *);
  void loadTextures(const std::string &);
  void drawAll() const;

  Player *getPlayer();
  Screen *getScreen();

private:
  void initKeymap();

private:
  int spawnTimer;
  int screenWidth, screenHeight;
  Screen *screen;
  Player *player;

  std::list<Bullet *> bullets;
  std::list<Enemy *> enemies;

  std::unordered_map<std::string, SDL_Texture *> textures;
  std::unordered_map<int, bool> keymap;
};
