#include "game.hpp"
#include "enemy.hpp"
#include <SDL_render.h>

Game::Game()
    : spawnTimer(1), screenWidth(DEFAULT_SCREEN_WIDTH),
      screenHeight(DEFAULT_SCREEN_HEIGHT),
      screen(new Screen(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT)),
      player(new Player()) {
  initKeymap();
  srand(time(NULL));
}

Game::Game(int w, int h)
    : spawnTimer(0), screenWidth(w), screenHeight(h), screen(new Screen(w, h)),
      player(new Player()) {
  initKeymap();
  srand(time(NULL));
}

Game::Game(int w, int h, position pos)
    : spawnTimer(0), screen(new Screen(w, h)),
      player(new Player(pos.x, pos.y)) {
  initKeymap();
  srand(time(NULL));
}

void Game::initKeymap() {
  keymap[SDL_SCANCODE_UP] = keymap[SDL_SCANCODE_W] = false;
  keymap[SDL_SCANCODE_DOWN] = keymap[SDL_SCANCODE_S] = false;
  keymap[SDL_SCANCODE_LEFT] = keymap[SDL_SCANCODE_A] = false;
  keymap[SDL_SCANCODE_RIGHT] = keymap[SDL_SCANCODE_D] = false;
  keymap[SDL_SCANCODE_SPACE] = false;
  keymap[SDL_SCANCODE_ESCAPE] = false;
}

Game::~Game() {
  if (screen != nullptr)
    delete screen;
  if (player != nullptr)
    delete player;

  for (Bullet *bullet : bullets) {
    delete bullet;
  }

  for (Enemy *enemy : enemies) {
    delete enemy;
  }

  for (auto const &[name, texture] : textures) {
    SDL_DestroyTexture(texture);
  }
}

int Game::inputHandle() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      return 1;

    case SDL_KEYDOWN:
      if (handleKeydown(&event.key) == -1)
        return 1;
      break;

    case SDL_KEYUP:
      if (handleKeyup(&event.key) == -1)
        return 1;
      break;

    default:
      break;
    }
  }
  updateState();
  return 0;
}

void Game::updateState() {
  updatePlayer();
  updateEnemies();
  updateBullets();
  spawnEnemies();
}

void Game::updatePlayer() {
  player->dx = player->dy = 0;
  player->reloadTick();

  if (keymap[SDL_SCANCODE_UP] || keymap[SDL_SCANCODE_W]) {
    player->dy = -player->getPlayerSpeed();
  }
  if (keymap[SDL_SCANCODE_DOWN] || keymap[SDL_SCANCODE_S]) {
    player->dy = player->getPlayerSpeed();
  }
  if (keymap[SDL_SCANCODE_RIGHT] || keymap[SDL_SCANCODE_D]) {
    player->dx = player->getPlayerSpeed();
  }
  if (keymap[SDL_SCANCODE_LEFT] || keymap[SDL_SCANCODE_A]) {
    player->dx = -player->getPlayerSpeed();
  }
  if (keymap[SDL_SCANCODE_SPACE] && !player->isReload()) {
    fireBullet();
  }

  player->updatePosition();
}

void Game::fireBullet() {
  position playerPos = player->getPosition();
  Bullet *bullet = new Bullet(playerPos.x, playerPos.y);
  bullet->setTexture(textures[BULLET_TEXTURE]);
  bullet->getSize();
  bullet->pos.x += (player->w / 2.0) - (bullet->w / 2.0);
  bullets.push_back(bullet);
}

void Game::updateBullets() {
  for (auto it = bullets.begin(); it != bullets.end();) {
    Bullet *bullet = *it;
    bullet->pos.x += bullet->dx;
    bullet->pos.y += bullet->dy;

    if (bullet->pos.y < 0) {
      delete bullet;
      auto tmp = it++;
      bullets.erase(tmp);
    } else {
      it++;
    }
  }
}

void Game::spawnEnemies() {
  if (--spawnTimer <= 0) {
    Enemy *enemy = new Enemy(rand() % screenWidth, 0.0);
    enemy->dy = enemy->getEnemySpeed() + (1 + rand() % 4);
    enemy->setTexture(textures[ENEMY_TEXTURE]);
    enemy->getSize();
    enemies.push_back(enemy);
    spawnTimer = DEFAULT_ENEMY_SPAWN_TIME + (rand() % 60);
  }
}

void Game::updateEnemies() {
  for (auto it = enemies.begin(); it != enemies.end();) {
    Enemy *enemy = *it;
    enemy->updatePosition();

    if (enemy->pos.y > screenHeight + enemy->h) {
      delete enemy;
      auto tmp = it++;
      enemies.erase(tmp);
    } else {
      it++;
    }
  }
}

void Game::drawAll() const {
  player->blit(screen->getRenderer());
  for (auto it = bullets.begin(); it != bullets.end(); ++it) {
    Bullet *bullet = *it;
    bullet->blit(screen->getRenderer());
  }
  for (auto it = enemies.begin(); it != enemies.end(); ++it) {
    Enemy *enemy = *it;
    enemy->blit(screen->getRenderer());
  }
}

int Game::handleKeydown(SDL_KeyboardEvent *event) {
  if (event->repeat == 0) { // don't want to repeat same actions
    keymap[event->keysym.scancode] = 1;
  }
  return (keymap[SDL_SCANCODE_ESCAPE] ? -1 : 1);
}

int Game::handleKeyup(SDL_KeyboardEvent *event) {
  if (event->repeat == 0) { // don't want to repeat same actions
    keymap[event->keysym.scancode] = 0;
  }
  return 0;
}

void Game::prepareScene(const color &color) const {
  auto renderer = screen->getRenderer();
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderClear(renderer);
}

void Game::presentScene() const { SDL_RenderPresent(screen->getRenderer()); }

void Game::setPlayer(int x, int y) {
  player->pos.x = x;
  player->pos.y = y;
}

void Game::loadTexture(const std::string &name, const std::string &filename,
                       SDL_Renderer *renderer) {
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                 "Loading %s", filename.c_str());
  SDL_Texture *newTexture = IMG_LoadTexture(renderer, filename.c_str());
  if (!newTexture) {
    std::cerr << "Coudn't load image with name: " << filename << std::endl;
  }
  textures[name] = newTexture;
}

void Game::loadTextures(const std::string &path) {
  loadTexture(PLAYER_TEXTURE, path + PLAYER_TEXTURE_PATH,
              screen->getRenderer());
  loadTexture(BULLET_TEXTURE, path + BULLET_TEXTURE_PATH,
              screen->getRenderer());
  loadTexture(ENEMY_TEXTURE, path + ENEMY_TEXTURE_PATH, screen->getRenderer());
  player->setTexture(textures[PLAYER_TEXTURE]);
  player->getSize();
}

Player *Game::getPlayer() { return player; }
Screen *Game::getScreen() { return screen; }
