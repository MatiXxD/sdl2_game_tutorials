#pragma once

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>

#include "color.hpp"
#include "exception.hpp"
#include "game_utility.hpp"
#include "screen.hpp"

#include "bullet.hpp"
#include "enemy.hpp"
#include "game_object.hpp"
#include "player.hpp"

constexpr int DEFAULT_FPS = 60;
constexpr int DEFAULT_SCREEN_WIDTH = 600;
constexpr int DEFAULT_SCREEN_HEIGHT = 900;
constexpr int DEFAULT_PLAYER_X = 270;
constexpr int DEFAULT_PLAYER_Y = 800;
constexpr int DEFAULT_RESET_TIMER = DEFAULT_FPS * 2;
constexpr int DEFAULT_ENEMY_SPAWN_TIME = 30;
constexpr int DEFAULT_ENEMY_BULLET_SPEED = 6;
constexpr char PLAYER_TEXTURE[] =
    "player"; // should be as player's texture filename
constexpr char BULLET_TEXTURE[] =
    "bullet"; // should be as bullet's texture filename
constexpr char ENEMY_TEXTURE[] =
    "enemy"; // should be as enemy's texture filename
constexpr char ENEMY_BULLET_TEXTURE[] =
    "enemy_bullet"; // should be as enemy's texture filename

class Game {
public:
  enum class status { QUIT, CONTINUE };

  Game();
  Game(int, int);
  ~Game();

  int inputHandle();
  int handleKeydown(SDL_KeyboardEvent *);
  int handleKeyup(SDL_KeyboardEvent *);

  void resetStage();
  void initPlayer();
  void clipPlayer();
  void spawnEnemies();

  void updateState();
  void updatePlayer();
  void updateBullets();
  void updateEnemies();

  void fireBullet();
  void enemyFireBullet(Enemy *);
  bool bulletHitEnemy(Bullet *);
  bool bulletHitPlayer(Bullet *);

  void prepareScene(const color &) const;
  void presentScene() const;

  void loadTexture(const std::string &, const std::string &, SDL_Renderer *);
  void loadTextures(const std::string &);
  void drawAll() const;

  Player *getPlayer();
  Screen *getScreen();

private:
  void initKeymap();

private:
  int spawnTimer;
  int stageTimer;
  int screenWidth, screenHeight;
  Screen *screen;
  Player *player;

  std::list<Bullet *> bullets;
  std::list<Enemy *> enemies;

  std::unordered_map<std::string, SDL_Texture *> textures;
  std::unordered_map<int, bool> keymap;
};
