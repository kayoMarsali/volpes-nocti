#pragma once
#include "defines.h"
#include "utils/logger/logger.h"
#include "types/entity.h"
#include "sprite.h"

class Level {
public:
    Level() {};
    ~Level();
    Level(i32 _width, i32 _height);
    b8 Save(const char *fileName);
    b8 Load(const char *fileName);
    b8 SetTile(i32 x, i32 y, i32 spriteIndex, i32 drawLayer);
    inline i32 Width() {return width;}
    inline i32 Height() {return height;}
    Entity *GetTile(i32 x, i32 y, i32 drawLayer);
private:
    i32 width;
    i32 height;
    Entity *foreground0Data;
    Entity *levelData;
    Entity *background0Data;
};