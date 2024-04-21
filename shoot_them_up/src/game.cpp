#include "game.hpp"


Game::Game(int w, int h) 
    : screen(new Screen(w, h)), player(new Player()) {
    
}

Game::Game(int w, int h, position pos) 
    : screen(new Screen(w, h)), player(new Player(pos.x, pos.y)) {
    
}

Game::~Game() {
    if(screen != nullptr) delete screen;
    if(player != nullptr) delete player;
}


int Game::inputHandle() {
    
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                return 1;

            default:
                break;
        }
    }

    return 0;

}

void Game::prepareScene(const color& color) const {
    auto renderer = screen->getRenderer();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void Game::presentScene() const {
    SDL_RenderPresent(screen->getRenderer());
}

Player* Game::getPlayer() { return player; }
Screen* Game::getScreen() { return screen; }
