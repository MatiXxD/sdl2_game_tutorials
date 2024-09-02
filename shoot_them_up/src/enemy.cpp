#include "enemy.hpp"
#include "game_object.hpp"

Enemy::Enemy()
    : GameObject(), speed(DEFAULT_ENEMY_SPEED), health(DEFALUT_ENEMY_HEALTH),
      shoot(false) {}

Enemy::Enemy(float x, float y)
    : GameObject(x, y), speed(DEFAULT_ENEMY_SPEED),
      health(DEFALUT_ENEMY_HEALTH), shoot(false) {}

Enemy::~Enemy() {}

void Enemy::blit(SDL_Renderer *renderer) {
  SDL_Rect destination;
  destination.x = pos.x;
  destination.y = pos.y;

  SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
  SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void Enemy::setTexture(SDL_Texture *t) { texture = t; }

void Enemy::getSize() { SDL_QueryTexture(texture, NULL, NULL, &w, &h); }

int Enemy::getEnemySpeed() const { return speed; }

bool Enemy::isDead() const { return health <= 0; }

void Enemy::hitEnemy() { health -= 1; }

void Enemy::updatePosition() { pos.y += dy; }

void Enemy::startReload(int maxReloadTime) {
  reload = (1 + std::rand() % maxReloadTime);
}

void Enemy::firstReload(int fps) {
  reload = fps * (1 + (std::rand() % 3));
}

void Enemy::reloadTick() {
  if (reload > 0) {
    reload--;
  }
}

void Enemy::startShoot(bool flag) { shoot = flag ? true : false; }

bool Enemy::isReload() const { return reload != 0; }

bool Enemy::isShoot() const { return shoot; }
