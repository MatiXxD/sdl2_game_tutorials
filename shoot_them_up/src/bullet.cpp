#include "bullet.hpp"

Bullet::Bullet()
    : GameObject(), dx(DEFAULT_BULLET_SPEED_X), dy(DEFAULT_BULLET_SPEED_Y),
      health(DEFAULT_BULLET_HEALTH) { }

Bullet::Bullet(float x, float y)
    : GameObject(x, y), dx(DEFAULT_BULLET_SPEED_X), dy(DEFAULT_BULLET_SPEED_Y),
      health(DEFAULT_BULLET_HEALTH) { }

Bullet::~Bullet() {}

void Bullet::blit(SDL_Renderer *renderer) {
  SDL_Rect destination;
  destination.x = pos.x;
  destination.y = pos.y;

  SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
  SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void Bullet::setTexture(SDL_Texture *t) { texture = t; }

void Bullet::getSize() { SDL_QueryTexture(texture, NULL, NULL, &w, &h); }

void Bullet::updatePosition() {
  pos.x += dx;
  pos.y -= dy;
}
