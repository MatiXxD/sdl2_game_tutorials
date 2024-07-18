#include "color.hpp"
#include "game.hpp"
#include <filesystem>
#include <iostream>

int main() {

  Game game(600, 900);
  game.setPlayer(270, 800);
  game.loadTextures(std::filesystem::current_path().string());

  while (true) {
    game.prepareScene(WHITE);

    int check = game.inputHandle();
    if (check == 1)
      break;

    game.drawAll();
    game.presentScene();
    SDL_Delay(16);
  }

  return 0;
}
