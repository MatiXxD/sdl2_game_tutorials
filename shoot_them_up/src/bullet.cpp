#include "bullet.hpp"

Bullet::Bullet() : GameObject(), dead(true), dx(0), dy(12) {}
Bullet::~Bullet() {}

void Bullet::loadTexture(const std::string &filename, SDL_Renderer *renderer) {
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                 "Loading %s", filename.c_str());
  texture = IMG_LoadTexture(renderer, filename.c_str());
  if (!texture) {
    std::cerr << "Coudn't load image with name: " << filename << std::endl;
  }
}

void Bullet::blit(SDL_Renderer *renderer) {
  SDL_Rect destination;
  destination.x = pos.x;
  destination.y = pos.y;

  SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
  SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void Bullet::updatePosition() {
  pos.x += dx;
  pos.y -= dy;
}

void Bullet::setDead(bool flag) {
  if (flag)
    dead = true;
  else
    dead = false;
}

bool Bullet::isDead() const { return dead == true; }
