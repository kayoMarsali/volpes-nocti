#include "entity.h"

Entity::Entity(i32 _spriteIndex, Vector2f position) 
: spriteIndex(_spriteIndex), position(position) {
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = spriteAtlas[spriteIndex].width;
    currentFrame.h = spriteAtlas[spriteIndex].height;
}
Entity::Entity(i32 _spriteIndex, f32 posX, f32 posY) 
: spriteIndex(_spriteIndex), position(posX, posY) {
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = spriteAtlas[spriteIndex].width;
    currentFrame.h = spriteAtlas[spriteIndex].height;
}