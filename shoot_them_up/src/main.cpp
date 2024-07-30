#include "color.hpp"
#include "game.hpp"
#include "game_utility.hpp"
#include <SDL_timer.h>
#include <cmath>
#include <filesystem>

int main(int argc, char** argv) {

  Game game(600, 900);
  game.setPlayer(270, 800);
  game.loadTextures(std::filesystem::current_path().string());

  long then = SDL_GetTicks();
  double remainder = 0.0;
  while (true) {
    game.prepareScene(BACKGROUND);

    int check = game.inputHandle();
    if (check == 1)
      break;

    game.drawAll();
    game.presentScene();
    capFrameRate(&then, &remainder);
  }

  return 0;
}
