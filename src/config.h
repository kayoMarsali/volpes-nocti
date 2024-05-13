#pragma once
#include "defines.h"

typedef struct video_config {
    i32 window_width = 640;
    i32 window_height = 480;
    b8 fullscreen = false;
    b8 vsync = false;
} video_config;

typedef struct audio_config {
    i8 bgm = 50;
    i8 sfx = 50;
    i8 environment = 50;
    i8 ui = 50;
    //i8 voice = 50;
} audio_config;

void SetupVideo(video_config *config);
void SetupAudio(audio_config *config);