#pragma once
#include "defines.h"
#include "utils/logger/logger.h"
#include "types/entity.h"

class Level {
public:
    Level() {};
    ~Level();
    Level(i32 _width, i32 _height);
    b8 SetTile(i32 x, i32 y, SDL_Texture *texture, i32 drawLayer);
    Entity *GetTile(i32 x, i32 y);
private:
    i32 width;
    i32 height;
    Entity *levelData;
};