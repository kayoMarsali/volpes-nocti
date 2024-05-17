#include "config.h"
#include "vendor/inih/cpp/INIReader.h"
#include "utils/logger/logger.h"


void SetupVideo(video_config *vconfig) {
    INIReader config("./config.ini");
    
    K_LOG_DEBUG("Video:");
    vconfig->window_width = config.GetInteger("Video", "window_width", 640);
    K_LOG_DEBUG("\twindow_widht: %i", vconfig->window_width);
    vconfig->window_height = config.GetInteger("Video", "window_height", 360);
    K_LOG_DEBUG("\twindow_height: %i", vconfig->window_height);
    vconfig->sprite_scale = vconfig->window_height / 360.f;
    K_LOG_DEBUG("\tsprite_scale: %f", vconfig->sprite_scale);
    i32 booltest = config.GetInteger("Video", "fullscreen", 0);
    (booltest > 0) ? vconfig->fullscreen = true : vconfig->fullscreen = false;
    K_LOG_DEBUG("\tfullscreen: %i", vconfig->fullscreen);
    booltest = config.GetInteger("Video", "vsync", 0);
    (booltest > 0) ? vconfig->vsync = true : vconfig->vsync = false;
    K_LOG_DEBUG("\tvsync: %i", vconfig->vsync);
}
void SetupAudio(audio_config *aconfig) {
    INIReader config("./config.ini");

    
    K_LOG_DEBUG("Audio:");
    aconfig->bgm = config.GetInteger("Audio","bgm", 50);
    K_LOG_DEBUG("\tbgm: %i", aconfig->bgm);
    aconfig->sfx = config.GetInteger("Audio","sfx", 50);
    K_LOG_DEBUG("\tsfx: %i", aconfig->sfx);
    aconfig->environment = config.GetInteger("Audio","environment", 50);
    K_LOG_DEBUG("\tenvironmental: %i", aconfig->environment);
    aconfig->ui = config.GetInteger("Audio","ui", 50);
    K_LOG_DEBUG("\tui: %i", aconfig->ui);

}