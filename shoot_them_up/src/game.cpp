#include "game.hpp"

Game::Game(int w, int h)
    : screen(new Screen(w, h)), player(new Player()), bullet(new Bullet()) {}

Game::Game(int w, int h, position pos)
    : screen(new Screen(w, h)), player(new Player(pos.x, pos.y)),
      bullet(new Bullet()) {}

Game::~Game() {
  if (screen != nullptr)
    delete screen;
  if (player != nullptr)
    delete player;
}

int Game::inputHandle() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      return 1;

    case SDL_KEYDOWN:
      if (handleKeydown(&event.key) == -1)
        return 1;
      break;

    case SDL_KEYUP:
      if (handleKeyup(&event.key) == -1)
        return 1;
      break;

    default:
      break;
    }
  }
  updateState();
  return 0;
}

void Game::updateState() {
  player->updatePosition();
  if (player->isShoot() && bullet->isDead()) {
    bullet->pos = player->pos;
    bullet->setDead(false);
  }
  bullet->updatePosition();
  if (bullet->pos.y < 0) {
    bullet->setDead(true);
  }
}

void Game::drawAll() const {
  player->blit(screen->getRenderer());
  if (!bullet->isDead()) {
    bullet->blit(screen->getRenderer());
  }
}

int Game::handleKeydown(SDL_KeyboardEvent *event) {
  if (event->repeat == 0) { // don't want to repeat same actions
    if (event->keysym.scancode == SDL_SCANCODE_UP ||
        event->keysym.scancode == SDL_SCANCODE_W) {
      player->moveUp(true);
    }

    if (event->keysym.scancode == SDL_SCANCODE_DOWN ||
        event->keysym.scancode == SDL_SCANCODE_S) {
      player->moveDown(true);
    }

    if (event->keysym.scancode == SDL_SCANCODE_RIGHT ||
        event->keysym.scancode == SDL_SCANCODE_D) {
      player->moveRight(true);
    }

    if (event->keysym.scancode == SDL_SCANCODE_LEFT ||
        event->keysym.scancode == SDL_SCANCODE_A) {
      player->moveLeft(true);
    }

    if (event->keysym.scancode == SDL_SCANCODE_SPACE) {
      player->startShoot(true);
    }

    if (event->keysym.scancode == SDL_SCANCODE_ESCAPE) {
      return -1;
    }
  }
  return 0;
}

int Game::handleKeyup(SDL_KeyboardEvent *event) {
  if (event->repeat == 0) { // don't want to repeat same actions
    if (event->keysym.scancode == SDL_SCANCODE_UP ||
        event->keysym.scancode == SDL_SCANCODE_W) {
      player->moveUp(false);
    }

    if (event->keysym.scancode == SDL_SCANCODE_DOWN ||
        event->keysym.scancode == SDL_SCANCODE_S) {
      player->moveDown(false);
    }

    if (event->keysym.scancode == SDL_SCANCODE_RIGHT ||
        event->keysym.scancode == SDL_SCANCODE_D) {
      player->moveRight(false);
    }

    if (event->keysym.scancode == SDL_SCANCODE_LEFT ||
        event->keysym.scancode == SDL_SCANCODE_A) {
      player->moveLeft(false);
    }

    if (event->keysym.scancode == SDL_SCANCODE_SPACE) {
      player->startShoot(false);
    }
  }
  return 0;
}

void Game::prepareScene(const color &color) const {
  auto renderer = screen->getRenderer();
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderClear(renderer);
}

void Game::presentScene() const { SDL_RenderPresent(screen->getRenderer()); }

void Game::setPlayer(int x, int y) {
  player->pos.x = x;
  player->pos.y = y;
}

void Game::loadTextures(const std::string &path) {
  player->loadTexture(path + "/textures/player.png", screen->getRenderer());
  bullet->loadTexture(path + "/textures/bullet.png", screen->getRenderer());
}

Player *Game::getPlayer() { return player; }
Screen *Game::getScreen() { return screen; }
