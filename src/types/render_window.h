#pragma once
#include "defines.h"
#include <SDL.h>
#include <SDL_image.h>
#include "entity.h"

class RenderWindow {
public:
    RenderWindow(const char* title, i32 width, i32 height);
    ~RenderWindow();

    SDL_Texture* LoadTexture(const char* filePath);

    void ClearScreen();
    void RenderTexture(Entity &entity);
    void DisplayScreen();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    RenderWindow() {};
};