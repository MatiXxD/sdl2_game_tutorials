#include <iostream>
#include <filesystem>
#include "game.hpp"
#include "color.hpp"


int main() {

    Game game(600, 900);
    auto screen = game.getScreen();
    auto player = game.getPlayer();

    player->getPosition().x = 270;
    player->getPosition().y = 800;
    player->loadTexture(std::filesystem::current_path().string()+"/textures/spaceship.png", screen->getRenderer());
    
    while(true) {
        game.prepareScene(WHITE);

        int check = game.inputHandle();
        if(check == 1) break;
        
        player->blit(screen->getRenderer());
        game.presentScene();
        SDL_Delay(16);
    }

    return 0;

}