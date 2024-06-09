#pragma once
#include "defines.h"
#include <SDL.h>
#include <map>

typedef struct Sprite {
    SDL_Texture *texture;
    i32 width;
    i32 height;
} Sprite;


extern std::map<i32, Sprite> spriteAtlas;