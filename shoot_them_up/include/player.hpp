#include "game_object.hpp"


class Player : public GameObject {

public:
    Player();
    Player(int x, int y);
    ~Player();

    void loadTexture(const std::string&, SDL_Renderer*);
    void blit(SDL_Renderer* renderer);

};