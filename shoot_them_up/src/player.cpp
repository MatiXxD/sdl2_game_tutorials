#include "player.hpp"


Player::Player() 
    : GameObject(), velocity(Velocity(4)), shoot(false) { }
Player::Player(int x, int y, int speed) 
    : GameObject(x, y), velocity(Velocity(speed)), shoot(false) { }

Player::~Player() {  }

void Player::loadTexture(const std::string& filename, SDL_Renderer* renderer) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename.c_str());
    texture = IMG_LoadTexture(renderer, filename.c_str());
    if(!texture) {
        std::cerr << "Coudn't load image with name: " << filename << std::endl;
    }
}

void Player::blit(SDL_Renderer* renderer) {
    SDL_Rect destination;
    destination.x = pos.x;
    destination.y = pos.y;

    SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
    SDL_RenderCopy(renderer, texture, NULL, &destination); 
}

void Player::moveUp(bool flag)     { velocity.up = flag ? true : false; }
void Player::moveDown(bool flag)   { velocity.down = flag ? true : false; }
void Player::moveRight(bool flag)  { velocity.right = flag ? true : false; }
void Player::moveLeft(bool flag)   { velocity.left = flag ? true : false; }
void Player::startShoot(bool flag) { shoot = flag ? true : false; }

void Player::updatePosition() {
    if(velocity.up)    pos.y -= velocity.speed;
    if(velocity.down)  pos.y += velocity.speed;
    if(velocity.right) pos.x += velocity.speed;
    if(velocity.left)  pos.x -= velocity.speed;
}

bool Player::isShoot() const { return shoot; }