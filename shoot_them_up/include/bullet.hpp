#pragma once
#include "game_object.hpp"

class Bullet : public GameObject {
public:
  Bullet();
  ~Bullet() override;

  void loadTexture(const std::string &, SDL_Renderer *) override;
  void blit(SDL_Renderer *renderer) override;

  void updatePosition();
  void setDead(bool);

  bool isDead() const;

private:
  bool dead;
  int dx;
  int dy;
};
