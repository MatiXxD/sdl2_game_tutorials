#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "exception.hpp"
#include "screen.hpp"
#include "color.hpp"

#include "player.hpp"


class Game {
public:
    enum class status { QUIT, CONTINUE };
    
    Game(int, int);
    Game(int, int, position);
    ~Game();

    int inputHandle();
    
    void prepareScene(const color&) const ;
    void presentScene() const ;
    
    Player* getPlayer();
    Screen* getScreen();


private:
    Screen* screen;
    Player* player;

};