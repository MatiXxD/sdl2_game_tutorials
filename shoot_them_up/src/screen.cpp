#include "screen.hpp"
#include "exception.hpp"

SDL_Renderer *Screen::getRenderer() const { return renderer; }
SDL_Window *Screen::getWindow() const { return window; }

Screen::Screen(int w, int h)
    : renderer(nullptr), window(nullptr), width(w), height(h) {

  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
    throw Exception("Couldn't initialize SDL");
  }

  window = SDL_CreateWindow("Shoot them up", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, width, height, 0);
  if (!window) {
    std::cerr << "Failed to open window: " << SDL_GetError() << std::endl;
    throw Exception("Failed to open window");
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    throw Exception("Failed to create renderer");
  }
}

Screen::~Screen() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

std::pair<int, int> Screen::getSize() const {
  return std::pair<int, int>(width, height);
}
