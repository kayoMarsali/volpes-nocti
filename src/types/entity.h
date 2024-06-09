#pragma once
#include <SDL.h>
#include "defines.h"
#include "utils/math/kmath.h"
#include "sprite.h"

class Entity {
public:
    Entity() {};
    Entity(i32 spriteIndex, Vector2f position);
    Entity(i32 spriteIndex, f32 posX, f32 posY);
    inline SDL_Texture* Texture() {return spriteAtlas[spriteIndex].texture;}
    inline void SwapTexture(i32 _spriteIndex) { 
        spriteIndex = _spriteIndex;
        currentFrame.w = spriteAtlas[spriteIndex].width;
        currentFrame.h = spriteAtlas[spriteIndex].height;
    }
    inline SDL_Rect CurrentFrame() {return currentFrame;}
    inline Vector2f& Position() {return position;}

private:
    i32 spriteIndex;
    SDL_Rect currentFrame;
    Vector2f position;
};