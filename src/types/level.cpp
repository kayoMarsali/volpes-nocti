#include "level.h"

Level::Level(i32 _width, i32 _height) 
: width(_width), height(_height) {
    levelData = (Entity*)malloc(sizeof(Entity)*width*height);
}

Level::~Level() {
    free(levelData);
    levelData = nullptr;
}

b8 Level::SetTile(i32 x, i32 y, SDL_Texture *texture, i32 drawLayer) {
    if(!levelData) {
        K_LOG_FATAL("Level data has not been initialized. Please Use Level(i32 _width, i32 _height) constructor to initialize the level before calling SetTile");
        return false;
    }

    levelData[y*width+x] = Entity(texture, {x*32.f, y*32.f}, drawLayer);
    return true;
}

Entity *Level::GetTile(i32 x, i32 y) {
    return &levelData[y*width+x];
}