#pragma once
#include "defines.h"
#include <SDL.h>
#include <SDL_image.h>
#include "entity.h"
#include "camera.h"
#include "config.h"

class RenderWindow {
public:
    RenderWindow(const char* title, video_config vconfig);
    ~RenderWindow();

    SDL_Texture* LoadTexture(const char* filePath);

    void ClearScreen();
    void RenderTexture(Entity &entity, Camera camerea);
    void DisplayScreen();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    RenderWindow() {};
};