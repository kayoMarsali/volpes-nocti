#pragma once
#include "defines.h"

class Camera {
public:
    Camera() {};
    Camera(f32 _x, f32 _y, i32 _speed) : posX(_x), posY(_y), speed(_speed) {};
    f32 posX, posY;
    i32 speed;
};