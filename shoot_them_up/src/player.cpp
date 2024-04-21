#include "player.hpp"


Player::Player() : GameObject() { }
Player::Player(int x, int y) : GameObject(x, y) { }
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
