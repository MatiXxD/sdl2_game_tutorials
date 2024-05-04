#pragma once
#include "game_object.hpp"


struct Velocity {
    int speed;
    bool up;
    bool down;
    bool right;
    bool left;

    Velocity(int s) : speed(s), up(false), down(false), right(false), left(false) { }
    Velocity(int s, int u, int d, int r, int l) : speed(s), up(u), down(d), right(r), left(l) { }
};

class Player : public GameObject {
public:
    Player();
    Player(int x, int y, int speed=2);
    ~Player() override;

    void loadTexture(const std::string&, SDL_Renderer*) override;
    void blit(SDL_Renderer* renderer) override;

    void moveUp(bool);
    void moveDown(bool);
    void moveRight(bool);
    void moveLeft(bool);
    void startShoot(bool);
    void updatePosition();

    bool isShoot() const;

private:
    Velocity velocity;
    bool shoot;
};