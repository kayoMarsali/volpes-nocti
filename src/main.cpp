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

#include "vendor/inih/cpp/INIReader.h"

b8 isRunning = false;

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
    video_config vconfig = {};
    SetupVideo(&vconfig);
    //Audio Settings
    audio_config aconfig = {};
    SetupAudio(&aconfig);

    RenderWindow* game = new RenderWindow("Volpes Nocti v0.0.1", vconfig);
    utils::math::seed_rng();

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
            }
        }

        game->ClearScreen();
        //Render Things;
        //Draw Level(Back)
        //Draw Player
        //Draw Enemies
        //Draw Level(Front)
        //Draw UI
        //Draw Debug
        game->DisplayScreen();
    }

    IMG_Quit();
    SDL_Quit();

    utils::Logger::Shutdown();
    return 0;
}