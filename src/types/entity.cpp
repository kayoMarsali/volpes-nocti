#include "entity.h"

Entity::Entity(SDL_Texture *texture, Vector2f position, i32 drawLayer) 
: texture(texture), position(position), drawLayer(drawLayer) {
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}
Entity::Entity(SDL_Texture *texture, f32 posX, f32 posY, i32 drawLayer) 
: texture(texture), position(posX, posY), drawLayer(drawLayer) {
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}