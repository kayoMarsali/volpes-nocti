#include <SDL.h>
#include <SDL_image.h>

#include "defines.h"
#include "config.h"
#include "utils/math/kmath.h"
#include <vector>
#include "utils/logger/logger.h"
#include "utils/strings/kstring.h"
#include "utils/filesystem/filesystem.h"

#include "types/entity.h"
#include "types/render_window.h"
#include "types/level.h"

#include "vendor/inih/cpp/INIReader.h"

#define EDIT_LEVEL 1

b8 isRunning = false;

i8 levelWidth = 40;
i8 levelHeight = 24;

i32 tileSize = 32;

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
    video_config vconfig;
    SetupVideo(&vconfig);
    //Audio Settings
    audio_config aconfig;
    SetupAudio(&aconfig);

    RenderWindow* game = new RenderWindow("Volpes Nocti v0.0.1", vconfig);
    utils::math::seed_rng();

    
    SDL_Texture* emptyTex = game->LoadTexture("./assets/empty.png");
    SDL_Texture* texture = game->LoadTexture("./assets/test0.png");
    SDL_Texture* gridTex = game->LoadTexture("./assets/test.png");
#if(EDIT_LEVEL == 1)
    Level *grid = new Level(levelWidth, levelHeight);
    for(i32 y = 0; y < levelHeight; ++y) {
        for(i32 x = 0; x < levelWidth; ++x) {
            grid->SetTile(x, y, gridTex, DRAW_LAYER_DEBUG);
        }
    }
#endif
    Level *testLevel = new Level(levelWidth, levelHeight);
    for(i32 y = 0; y < levelHeight; ++y) {
        for(i32 x = 0; x < levelWidth; ++x) {
            testLevel->SetTile(x, y, emptyTex, DRAW_LAYER_LEVEL);
        }
    }
    
    isRunning = true;
    while(isRunning) {
        utils::math::run_rng();

        SDL_Event ev;
        while(SDL_PollEvent(&ev)) {
            switch(ev.type) {
                case SDL_QUIT:
                    isRunning = false;
                    K_LOG_DEBUG("SDL_QUIT!");
                    break;
                case SDL_MOUSEBUTTONDOWN:
#if(EDIT_LEVEL == 1)
                        i32 mouse_x, mouse_y;
                        if(SDL_GetMouseState(&mouse_x, &mouse_y) == SDL_BUTTON_LEFT) {
                            i32 x_pos = SDL_floor((mouse_x/vconfig.sprite_scale)/32);
                            i32 y_pos = SDL_floor((mouse_y/vconfig.sprite_scale)/32);

                            if(x_pos < 0 || x_pos > levelWidth || y_pos < 0 || y_pos > levelHeight) {
                                break;
                            }

                            Entity *e = testLevel->GetTile(x_pos, y_pos);
                            if(e->Texture() == texture) {
                                e->SwapTexture(emptyTex);
                            } else {
                                e->SwapTexture(texture);
                            }
                        }
#endif
                    break;
            }
        }

        game->ClearScreen();

#if(EDIT_LEVEL == 1)
        for (int y = 0; y < levelHeight; y++) {
            for(int x = 0; x < levelWidth; x++) {
                game->RenderTexture(*grid->GetTile(x, y));
            }
        }
#endif

//Draw Backgrounds
//Drawl Level
        for (int y = 0; y < levelHeight; y++) {
            for(int x = 0; x < levelWidth; x++) {
                game->RenderTexture(*testLevel->GetTile(x, y));
            }
        }
//Draw Player
//Draw Items
//Draw Enemies
//Draw Effects
//Draw Foregrounds
//Draw UI

        game->DisplayScreen();
    }
    delete testLevel;
#if(EDIT_LEVEL == 1)
    delete grid;
#endif
    IMG_Quit();
    SDL_Quit();

    utils::Logger::Shutdown();
    return 0;
}