#include "player.hpp"

Player::Player()
    : GameObject(), shoot(false), speed(DEFAULT_PLAYER_SPEED),
      reload(DEFAULT_PLAYER_RELOAD), health(DEFAULT_PLAYER_HEALTH) {}

Player::Player(float x, float y)
    : GameObject(x, y), shoot(false), speed(DEFAULT_PLAYER_SPEED),
      reload(DEFAULT_PLAYER_RELOAD), health(DEFAULT_PLAYER_HEALTH) {}

Player::~Player() {}

void Player::blit(SDL_Renderer *renderer) {
  SDL_Rect destination;
  destination.x = pos.x;
  destination.y = pos.y;

  SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
  SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void Player::setTexture(SDL_Texture *t) { texture = t; }

void Player::getSize() { SDL_QueryTexture(texture, NULL, NULL, &w, &h); }

int Player::getPlayerSpeed() const { return speed; }

void Player::updatePosition() {
  pos.x += dx;
  pos.y += dy;
}

void Player::reloadTick() {
  if (reload > 0)
    reload--;
  else if (reload <= 0)
    reload = DEFAULT_PLAYER_RELOAD;
}

void Player::startShoot(bool flag) { shoot = flag ? true : false; }

bool Player::isReload() const { return reload != 0; }

bool Player::isShoot() const { return shoot; }
