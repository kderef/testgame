#pragma once

#include "raylib.h"
#include "../input.h"
#include "../log.h"
#include "../sys.h"

#include <stdbool.h>

typedef struct game {
    bool running;
} game_t;

game_t game_create() {
    game_t g = {
        .running = true,
    };

    return g;
}

// Create window and context
void game_init(game_t* g)  {
    // --- flags
    ConfigFlags config_flags =
        FLAG_MSAA_4X_HINT | 
        FLAG_WINDOW_RESIZABLE |
        FLAG_VSYNC_HINT;

    SetConfigFlags(config_flags);
    
    // --- init logging
    SetTraceLogCallback(rl_log_callback);
    log_set_minimum_level(0);
    
    errno_t error = log_open_file();    
    if (error != 0) {
        error("Failed to open log file: %s", strerror(errno));
    }
    
    // --- create window
    const char* title = "game";
    int width = 1000;
    int height = 800;

    InitWindow(width, height, title);
    InitAudioDevice();

    // --- set FPS target
    Monitor monitor = monitor_get_info();

    if (monitor.refresh > 0)
        SetTargetFPS(monitor.refresh);

    
}

bool game_should_close(game_t* g) {
    bool window_should_close = WindowShouldClose();

    bool close = window_should_close || !(g->running);

    return close;
}

void game_close(game_t* g) {
    capture_mouse(false);
    
    CloseAudioDevice();
    CloseWindow();

    // Close logging
    log_close();
}
