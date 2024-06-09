#include <SDL.h>
#include <SDL_image.h>

#include "defines.h"
#include "config.h"
#include "utils/math/kmath.h"
#include "utils/logger/logger.h"
#include "utils/strings/kstring.h"
#include "utils/filesystem/filesystem.h"

#include "types/entity.h"
#include "types/render_window.h"
#include "types/camera.h"
#include "types/level.h"

#include "vendor/inih/cpp/INIReader.h"

#define EDIT_LEVEL 1

b8 isRunning = false;

i8 levelWidth = 80;
i8 levelHeight = 12;

i32 tileSize = 32;


video_config vconfig;
audio_config aconfig;

Level *testLevel = nullptr;
Camera camera;

const u8* keystate = SDL_GetKeyboardState(NULL);

i32 editLayer = DRAW_LAYER_LEVEL;

void ProcessInput();

int main(int argc, char *argv[]) {
    utils::Logger::Initialize();

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        K_LOG_FATAL("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    if(!IMG_Init(IMG_INIT_PNG)) {
        K_LOG_FATAL("IMG_Init failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    //Video Settings
    SetupVideo(&vconfig);
    //Audio Settings
    SetupAudio(&aconfig);

    RenderWindow* game = new RenderWindow("Volpes Nocti v0.0.1", vconfig);
    utils::math::seed_rng();
    K_LOG_DEBUG("Window Created.");
    
    Sprite sprite = {};
    sprite.height = 32;
    sprite.width = 32;
    
    SDL_Texture* emptyTex = game->LoadTexture("./assets/empty.png");
    sprite.texture = emptyTex;
    spriteAtlas[0] = sprite;

    SDL_Texture* texture = game->LoadTexture("./assets/test0.png");
    sprite.texture = texture;
    spriteAtlas[1] = sprite;

    SDL_Texture* halfTex = game->LoadTexture("./assets/bottom_half0.png");
    sprite.texture = halfTex;
    spriteAtlas[2] = sprite;

    SDL_Texture* gridTex = game->LoadTexture("./assets/test.png");
    sprite.texture = gridTex;
    spriteAtlas[3] = sprite;

    testLevel = new Level(levelWidth, levelHeight);
    for(i32 y = 0; y < testLevel->Height(); ++y) {
        for(i32 x = 0; x < testLevel->Width(); ++x) {
            testLevel->SetTile(x, y, 3, DRAW_LAYER_BKGND0);
            testLevel->SetTile(x, y, 0, DRAW_LAYER_LEVEL);
            testLevel->SetTile(x, y, 0, DRAW_LAYER_FRGND0);
        }
    }

    camera = Camera(0, 0, 5);

    isRunning = true;
    while(isRunning) {
        utils::math::run_rng();

        ProcessInput();

        game->ClearScreen();

//Draw Backgrounds

        for (int y = 0; y < testLevel->Height(); y++) {
            for(int x = 0; x < testLevel->Width(); x++) {
                game->RenderTexture(*testLevel->GetTile(x, y, DRAW_LAYER_BKGND0), camera);
            }
        }
//Drawl Level
        for (int y = 0; y < testLevel->Height(); y++) {
            for(int x = 0; x < testLevel->Width(); x++) {
                game->RenderTexture(*testLevel->GetTile(x, y, DRAW_LAYER_LEVEL), camera);
            }
        }
//Draw Player
//Draw Items
//Draw Enemies
//Draw Effects
//Draw Foregrounds
        for (int y = 0; y < testLevel->Height(); y++) {
            for(int x = 0; x < testLevel->Width(); x++) {
                game->RenderTexture(*testLevel->GetTile(x, y, DRAW_LAYER_FRGND0), camera);
            }
        }
        
//Draw UI

        game->DisplayScreen();
        
    }
    delete testLevel;
    IMG_Quit();
    SDL_Quit();

    utils::Logger::Shutdown();
    return 0;
}

void ProcessInput() {
    SDL_Event ev;

    while(SDL_PollEvent(&ev)) {        
        switch(ev.type) {
            case SDL_QUIT: {
                isRunning = false;
                K_LOG_DEBUG("SDL_QUIT!");
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                #if(EDIT_LEVEL == 1)
                i32 mouse_x, mouse_y;
                if(SDL_GetMouseState(&mouse_x, &mouse_y) == SDL_BUTTON_LEFT) {
                    i32 x_pos = SDL_floor(((mouse_x/vconfig.sprite_scale)+camera.posX)/tileSize);
                    i32 y_pos = SDL_floor(((mouse_y/vconfig.sprite_scale)+camera.posY)/tileSize);

                    if(x_pos < 0 || x_pos > testLevel->Width() || y_pos < 0 || y_pos > testLevel->Height()) {
                        break;
                    }

                    Entity *e = testLevel->GetTile(x_pos, y_pos, editLayer);

                    if(e->Texture() == spriteAtlas[2].texture) {
                        e->SwapTexture(0);
                    } else if(e->Texture() == spriteAtlas[0].texture) {
                        e->SwapTexture(1);
                    } else {
                        e->SwapTexture(2);
                    }
                } else {
                    switch(editLayer) {
                        case DRAW_LAYER_LEVEL:
                            editLayer = DRAW_LAYER_FRGND0;
                            break;
                        case DRAW_LAYER_FRGND0:
                        default:
                            editLayer = DRAW_LAYER_LEVEL;
                        
                    }
                }
                #endif
                break;
            }
            case SDL_KEYDOWN: {
                #if(EDIT_LEVEL == 1)
                if(ev.key.keysym.sym == SDLK_o) {
                    testLevel->Save("./testLevel.dat");
                }
                if(ev.key.keysym.sym == SDLK_i) {
                    testLevel->Load("./testLevel.dat");
                }
                #endif
                break;
            }
        }
    }

    if(keystate[SDL_SCANCODE_LEFT]) {
        camera.posX -= camera.speed;
        if(camera.posX < 0) {
            camera.posX = 0;
        }
    }
    if(keystate[SDL_SCANCODE_RIGHT]) {
        camera.posX += camera.speed;
        if(camera.posX + (vconfig.window_width/2) > (levelWidth * tileSize)) {
            camera.posX = (levelWidth * tileSize) - (vconfig.window_width/2);
        }
    }
    if(keystate[SDL_SCANCODE_UP]) {
    camera.posY -= camera.speed;
        if(camera.posY < 0) {
            camera.posY = 0;
        }
    }
    if(keystate[SDL_SCANCODE_DOWN]) {
        camera.posY += camera.speed;
        if(camera.posY > (levelHeight * tileSize - (vconfig.window_height/2))) {
            camera.posY = (levelHeight * tileSize) - (vconfig.window_height/2);
        }
    }

    
}