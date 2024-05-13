#include "config.h"
#include "vendor/inih/cpp/INIReader.h"
#include "utils/logger/logger.h"


void SetupVideo(video_config *vconfig) {
    INIReader config("./config.ini");
    
    K_LOG_DEBUG("Video:");
    vconfig->window_width = config.GetInteger("Video", "window_width", vconfig->window_width);
    K_LOG_DEBUG("\twindow_widht: %i", vconfig->window_width);
    vconfig->window_height = config.GetInteger("Video", "window_height", vconfig->window_height);
    K_LOG_DEBUG("\twindow_height: %i", vconfig->window_height);
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
    aconfig->bgm = config.GetInteger("Audio","bgm", aconfig->bgm);
    K_LOG_DEBUG("\tbgm: %i", aconfig->bgm);
    aconfig->sfx = config.GetInteger("Audio","sfx", aconfig->sfx);
    K_LOG_DEBUG("\tsfx: %i", aconfig->sfx);
    aconfig->environment = config.GetInteger("Audio","environment", aconfig->environment);
    K_LOG_DEBUG("\tenvironmental: %i", aconfig->environment);
    aconfig->ui = config.GetInteger("Audio","ui", aconfig->ui);
    K_LOG_DEBUG("\tui: %i", aconfig->ui);

}