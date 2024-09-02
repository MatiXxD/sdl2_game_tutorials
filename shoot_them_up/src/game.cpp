#include "game.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include <SDL_render.h>
#include <filesystem>

Game::Game()
    : spawnTimer(1), stageTimer(0), screenWidth(DEFAULT_SCREEN_WIDTH),
      screenHeight(DEFAULT_SCREEN_HEIGHT),
      screen(new Screen(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT)),
      player(nullptr) {
  initKeymap();
  srand(time(NULL));
}

Game::Game(int w, int h)
    : spawnTimer(0), stageTimer(0), screenWidth(w), screenHeight(h),
      screen(new Screen(w, h)), player(nullptr) {
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

void Game::resetStage() {
  for (Bullet *bullet : bullets) {
    delete bullet;
  }

  for (Enemy *enemy : enemies) {
    delete enemy;
  }

  initPlayer();
  spawnTimer = 0;
  stageTimer = 5 * DEFAULT_FPS;
}

void Game::updateState() {
  std::cout << stageTimer << "\t" << (player == nullptr ? "DEAD" : "OK")
            << std::endl;
  if (player == nullptr && --stageTimer <= 0) {
    resetStage();
  }

  updatePlayer();
  clipPlayer();

  updateEnemies();
  updateBullets();
  spawnEnemies();
}

void Game::initPlayer() {
  player = new Player(DEFAULT_PLAYER_X, DEFAULT_PLAYER_Y);
  player->setTexture(textures[PLAYER_TEXTURE]);
  player->getSize();
}

void Game::clipPlayer() {
  if (player == nullptr) {
    return;
  }

  if (player->pos.x < 0) {
    player->pos.x = 0;
  }
  if (player->pos.y > DEFAULT_SCREEN_HEIGHT - player->h) {
    player->pos.y = DEFAULT_SCREEN_HEIGHT - player->h;
  }
  if (player->pos.x > DEFAULT_SCREEN_WIDTH - player->w) {
    player->pos.x = DEFAULT_SCREEN_WIDTH - player->w;
  }
  if (player->pos.y < DEFAULT_SCREEN_HEIGHT / 2.0) {
    player->pos.y = DEFAULT_SCREEN_HEIGHT / 2.0;
  }
}

void Game::updatePlayer() {
  if (player == nullptr)
    return;

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
  player->startReload();
  position playerPos = player->getPosition();

  Bullet *bullet = new Bullet(playerPos.x, playerPos.y);
  bullet->setTexture(textures[BULLET_TEXTURE]);
  bullet->getSize();
  bullet->pos.x += (player->w / 2.0) - (bullet->w / 2.0);
  bullet->bt = BulletType::PLAYER_BULLET;
  bullets.push_back(bullet);
}

void Game::enemyFireBullet(Enemy *enemy) {
  enemy->startReload(2 * DEFAULT_FPS);
  position enemyPos = enemy->getPosition();

  Bullet *bullet = new Bullet(enemyPos.x, enemyPos.y);
  bullet->setTexture(textures[ENEMY_BULLET_TEXTURE]);
  bullet->getSize();
  bullet->pos.x += (enemy->w / 2.0) - (enemy->w / 2.0);
  bullet->bt = BulletType::ENEMY_BULLET;

  float dx, dy;
  calcSlope(player->pos.x + (player->w / 2.0),
            player->pos.y + (player->h / 2.0), enemy->pos.x, enemy->pos.y, &dx,
            &dy);
  bullet->setMove(dx * DEFAULT_ENEMY_SPEED, dy * DEFAULT_ENEMY_SPEED);

  bullets.push_back(bullet);
}

bool Game::bulletHitEnemy(Bullet *bullet) {
  for (auto it = enemies.begin(); it != enemies.end(); it++) {
    Enemy *enemy = *it;
    if (bullet->bt == BulletType::PLAYER_BULLET &&
        collision_detection(bullet->pos.x, bullet->pos.y, bullet->w, bullet->h,
                            enemy->pos.x, enemy->pos.y, enemy->w, enemy->h)) {
      bullet->setDead();
      enemy->hitEnemy();
      return true;
    }
  }
  return false;
}

bool Game::bulletHitPlayer(Bullet *bullet) {
  if (bullet->bt == BulletType::PLAYER_BULLET && player != nullptr &&
      collision_detection(bullet->pos.x, bullet->pos.y, bullet->w, bullet->h,
                          player->pos.x, player->pos.y, player->w, player->h)) {
    bullet->setDead();
    delete player;
    return true;
  }
  return false;
}

void Game::updateBullets() {
  for (auto it = bullets.begin(); it != bullets.end();) {
    Bullet *bullet = *it;
    bullet->pos.x += bullet->dx;
    bullet->pos.y += bullet->dy;

    if (bullet->pos.y < 0 || bullet->pos.y > DEFAULT_SCREEN_HEIGHT ||
        bullet->pos.x < 0 || bullet->pos.x > DEFAULT_SCREEN_WIDTH ||
        bulletHitEnemy(bullet) /* || bulletHitPlayer(bullet) */) { // FIX: bulletHitPlayer lead to crash
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
    enemy->firstReload(DEFAULT_FPS);
    enemies.push_back(enemy);
    spawnTimer = DEFAULT_ENEMY_SPAWN_TIME + (rand() % 60);
  }
}

void Game::updateEnemies() {
  for (auto it = enemies.begin(); it != enemies.end();) {
    Enemy *enemy = *it;
    enemy->updatePosition();

    if (enemy->pos.y > screenHeight + enemy->h || enemy->isDead()) {
      delete enemy;
      auto tmp = it++;
      enemies.erase(tmp);
    } else {
      enemy->reloadTick();
      if (player != nullptr && !enemy->isReload()) {
        enemyFireBullet(enemy);
      }
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
  std::string texturePathString = "";
  std::filesystem::path projectPath{path};
  for (auto const &dirEntry : std::filesystem::directory_iterator{path}) {
    if (dirEntry.path().string().find("textures") != std::string::npos) {
      texturePathString = dirEntry.path().string();
    }
  }
  if (texturePathString == "")
    return;

  std::filesystem::path texturePath{texturePathString};
  for (auto const &dirEntry :
       std::filesystem::directory_iterator{texturePath}) {
    if (dirEntry.is_directory())
      continue;
    std::string texture = dirEntry.path().stem().string();
    loadTexture(texture, dirEntry.path().string(), screen->getRenderer());
  }
}

Player *Game::getPlayer() { return player; }
Screen *Game::getScreen() { return screen; }
