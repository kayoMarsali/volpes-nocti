#pragma once
#include <SDL.h>
#include "defines.h"
#include "utils/math/kmath.h"

class Entity {
public:
    Entity() {};
    Entity(SDL_Texture *texture, Vector2f position, i32 drawLayer);
    Entity(SDL_Texture *texture, f32 posX, f32 posY, i32 drawLayer);
    inline SDL_Texture* Texture() {return texture;}
    inline void SwapTexture(SDL_Texture *_texture) { texture = _texture;}
    inline SDL_Rect CurrentFrame() {return currentFrame;}
    inline i32 DrawLayer() {return drawLayer;}
    inline Vector2f& Position() {return position;}

private:
    SDL_Texture *texture;
    SDL_Rect currentFrame;
    Vector2f position;
    i32 drawLayer;
};