#include "render_window.h"
#include "utils/logger/logger.h"

static u8 windowScaleH = 1;
static u8 windowScaleV = 1;

RenderWindow::RenderWindow(const char* title, i32 width, i32 height) : window(nullptr), renderer(nullptr) {
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if(this->window == nullptr) {
        K_LOG_FATAL("Failed to create SDL Window. Error: %s", SDL_GetError());
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(this->renderer == nullptr) {
        K_LOG_FATAL("Failed to create SDL Renderer. Error: ", SDL_GetError());
    }

    windowScaleH = width/640;
    windowScaleV = height/480;
}

RenderWindow::~RenderWindow() {
    SDL_DestroyRenderer(this->renderer);
    this->renderer = nullptr;
    SDL_DestroyWindow(this->window);
    this->window = nullptr;
}

SDL_Texture* RenderWindow::LoadTexture(const char* filePath) {
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(this->renderer, filePath);

    if(nullptr == texture) {
        K_LOG_ERROR("Failed to load image texture. Error: %s", SDL_GetError());
        return nullptr;
    }

    return texture;
}

void RenderWindow::ClearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 20, 255);
	SDL_RenderClear(renderer);
}

void RenderWindow::RenderTexture(Entity &entity) {
    SDL_Rect src;
    src.x = entity.CurrentFrame().x;
    src.y = entity.CurrentFrame().y;
    src.w = entity.CurrentFrame().w;
    src.h = entity.CurrentFrame().h;

    SDL_Rect dst;
    dst.x = entity.Position().x * windowScaleH;
    dst.y = entity.Position().y * windowScaleV;
    dst.w = 32 * windowScaleH;
    dst.h = 32 * windowScaleV;
    
    SDL_RenderCopy(this->renderer, entity.Texture(), &src, &dst);
}

void RenderWindow::DisplayScreen() {
    
	SDL_RenderPresent(renderer);
}