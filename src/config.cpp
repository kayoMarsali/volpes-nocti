#include "config.h"
#include "vendor/inih/cpp/INIReader.h"
#include "utils/logger/logger.h"
#include "SDL.h"

void SetupVideo(video_config *vconfig) {
    INIReader config("./config.ini");
    
    vconfig->window_width = config.GetInteger("Video", "window_width", 640);
    vconfig->window_height = config.GetInteger("Video", "window_height", 360);
    vconfig->sprite_scale = SDL_ceilf(vconfig->window_height / 360.f);
    i32 booltest = config.GetInteger("Video", "fullscreen", 0);
    (booltest > 0) ? vconfig->fullscreen = true : vconfig->fullscreen = false;
    booltest = config.GetInteger("Video", "vsync", 0);
    (booltest > 0) ? vconfig->vsync = true : vconfig->vsync = false;

    K_LOG_DEBUG("Video:");
    K_LOG_DEBUG("\twindow_widht: %i", vconfig->window_width);
    K_LOG_DEBUG("\twindow_height: %i", vconfig->window_height);
    K_LOG_DEBUG("\tsprite_scale: %f", vconfig->sprite_scale);
    K_LOG_DEBUG("\tfullscreen: %i", vconfig->fullscreen);
    K_LOG_DEBUG("\tvsync: %i", vconfig->vsync);
}
void SetupAudio(audio_config *aconfig) {
    INIReader config("./config.ini");

    
    aconfig->bgm = config.GetInteger("Audio","bgm", 50);
    aconfig->sfx = config.GetInteger("Audio","sfx", 50);
    aconfig->environment = config.GetInteger("Audio","environment", 50);
    aconfig->ui = config.GetInteger("Audio","ui", 50);

    K_LOG_DEBUG("Audio:");
    K_LOG_DEBUG("\tbgm: %i", aconfig->bgm);
    K_LOG_DEBUG("\tsfx: %i", aconfig->sfx);
    K_LOG_DEBUG("\tenvironmental: %i", aconfig->environment);
    K_LOG_DEBUG("\tui: %i", aconfig->ui);

}