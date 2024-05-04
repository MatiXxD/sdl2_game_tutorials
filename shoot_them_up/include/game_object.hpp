#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



struct position {
    int x;
    int y;

    position() : x(0), y(0) { }
    position(int x, int y) : x(x), y(y) { }      
};


class GameObject {
public:
    GameObject() : pos(position(0, 0)), texture(nullptr) { }
    GameObject(int x, int y) : pos(position(x, y)), texture(nullptr) { }
    virtual ~GameObject() { SDL_DestroyTexture(texture); }

    virtual void loadTexture(const std::string&, SDL_Renderer*)=0;
    virtual void blit(SDL_Renderer* renderer)=0;
    
    SDL_Texture* getTexture() { return texture; }
    position getPosition() const { return pos; }
    position& getPosition() { return pos; }

public:
    position pos;

protected:
    SDL_Texture* texture;

};