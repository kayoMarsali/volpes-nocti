#include "level.h"
#include <vector>
#include "utils/filesystem/filesystem.h"

Level::Level(i32 _width, i32 _height) 
: width(_width), height(_height) {
    levelData = (Entity*)malloc(sizeof(Entity)*width*height);
    foreground0Data = (Entity*)malloc(sizeof(Entity)*width*height);
    background0Data = (Entity*)malloc(sizeof(Entity)*width*height);
}

Level::~Level() {
    free(levelData);
    levelData = nullptr;
    free(foreground0Data);
    foreground0Data = nullptr;
    free(background0Data);
    background0Data = nullptr;
}

b8 Level::SetTile(i32 x, i32 y, i32 spriteIndex, i32 drawLayer) {
    Sprite sprite = spriteAtlas[spriteIndex];
    switch(drawLayer) {
        case DRAW_LAYER_LEVEL:
        {
            if(!levelData) {
                K_LOG_FATAL("Background0 data has not been initialized. Please Use Level(i32 _width, i32 _height) constructor to initialize the level before calling SetTile");
                return false;
            }
            levelData[y*width+x] = Entity(spriteIndex, {x*sprite.width, y*sprite.width});
            return true;
        }
        case DRAW_LAYER_BKGND0:
        {
            if(!background0Data) {
                K_LOG_FATAL("Level data has not been initialized. Please Use Level(i32 _width, i32 _height) constructor to initialize the level before calling SetTile");
                return false;
            }
            background0Data[y*width+x] = Entity(spriteIndex, {x*sprite.width, y*sprite.width});
            return true;
        }
        
        case DRAW_LAYER_FRGND0:
        {
            if(!foreground0Data) {
                K_LOG_FATAL("Foreground data has not been initialized. Please Use Level(i32 _width, i32 _height) constructor to initialize the level before calling SetTile");
                return false;
            }
            foreground0Data[y*width+x] = Entity(spriteIndex, {x*sprite.width, y*sprite.width});
            return true;
        }
        default:
            K_LOG_INFO("Layer not implemented, could not set tile.");
            return false;
    }
}

Entity *Level::GetTile(i32 x, i32 y, i32 drawLayer) {
    if(drawLayer == DRAW_LAYER_LEVEL) {
        return &levelData[y*width+x];
    } else if(drawLayer == DRAW_LAYER_BKGND0) {
        return &background0Data[y*width+x];
    } else if(drawLayer == DRAW_LAYER_FRGND0) {
        return &foreground0Data[y*width+x];
    }

    return nullptr;
}

b8 Level::Save(const char *file) {
    FileHandle levelHandle;
    utils::filesystem::Open(file, FileModes::WRITE, true, &levelHandle);
    u8 *data = nullptr;
    u64 byteCount = sizeof(width) + sizeof(height) + (sizeof(Entity) * width * height) +
                    (sizeof(Entity) * width * height) + (sizeof(Entity) * width * height) + 8;
    K_LOG_DEBUG("%llu", byteCount);
    data = (u8 *)SDL_malloc(byteCount);
    //setup data
    //Header 1
    data[0] = 75;
    data[1] = 77;
    data[2] = 71;
    data[3] = 69;
    //Header 2
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = 1;
    u64 written = 8;
    memcpy(data+written, static_cast<const u8 *>(static_cast<const void *>(&width)), sizeof(width));
    written += sizeof(width);

    memcpy(data+written, static_cast<const u8 *>(static_cast<const void *>(&height)), sizeof(height));
    written += sizeof(height);

    memcpy(data+written, levelData, sizeof(Entity)*width*height);
    written += sizeof(Entity)*width*height;
    
    memcpy(data+written, foreground0Data, sizeof(Entity)*width*height);
    written += sizeof(Entity)*width*height;

    
    memcpy(data+written, background0Data, sizeof(Entity)*width*height);
    written += sizeof(Entity)*width*height;
    //write data to file
    utils::filesystem::Write(&levelHandle, byteCount, data, &written);
    K_LOG_DEBUG("%llu bytes written.", written);

    utils::filesystem::Close(&levelHandle);
    SDL_free(data);
    K_LOG_DEBUG("Level Saved.");
    return true;
}

b8 Level::Load(const char *file) {
    if(!utils::filesystem::Exists(file)) {
        K_LOG_WARN("Cannot load level. File: %s does not exist.", file);
        return false;
    }
    //TODO: Load Level
    FileHandle levelFile;
    utils::filesystem::Open(file, FileModes::READ, true, &levelFile);
    u8* levelFileData = nullptr;
    u64 dataRead = 0;
    utils::filesystem::ReadAllBytes(&levelFile, &levelFileData, &dataRead);
    if(levelFileData[0] != 75 || levelFileData[1] != 77 || levelFileData[2] != 71 || levelFileData[3] != 69) {
        K_LOG_WARN("Improper Header.");
        return false;
    }
    u64 it = 8;
    width = *reinterpret_cast<i32 *>(levelFileData+it);
    it += sizeof(i32);
    height = *reinterpret_cast<i32 *>(levelFileData+it);
    it += sizeof(i32);
    free(levelData);
    levelData = (Entity *)malloc(sizeof(Entity)*width*height);
    memcpy(levelData, levelFileData+it, sizeof(Entity)*width*height);
    it += sizeof(Entity)*width*height;
    free(foreground0Data);
    foreground0Data = (Entity *)malloc(sizeof(Entity)*width*height);
    memcpy(foreground0Data, levelFileData+it, sizeof(Entity)*width*height);
    it += sizeof(Entity)*width*height;
    free(background0Data);
    background0Data = (Entity *)malloc(sizeof(Entity)*width*height);
    memcpy(background0Data, levelFileData+it, sizeof(Entity)*width*height);
    it += sizeof(Entity)*width*height;
    K_LOG_DEBUG("%llu bytes read", dataRead);
    K_LOG_DEBUG("Level Loaded.");
    return true;
    // load level
}