#include "raylib.h"
#include "camera.c"
#include <stdio.h>
#include <stdbool.h>

Camera3D camera_init() {
    Camera3D cam = {
        .fovy = 90,
        .position = {1, 1, 1},
        .projection = CAMERA_PERSPECTIVE,
        .up = {0, 1, 0},
        .target = {10, 1, 10},
    };

  return cam;
}

void capture_mouse(bool capture) {
    if (capture) DisableCursor();
    else EnableCursor();
}



int main(int argc, char** argv) {
    // --- config
    const char* TITLE = "Simple Raylib Template";
    const int WIDTH = 1280;
    const int HEIGHT = 768;

    // --- flags
    ConfigFlags config_flags =
        FLAG_MSAA_4X_HINT | 
        FLAG_WINDOW_RESIZABLE |
        FLAG_VSYNC_HINT;

    SetConfigFlags(config_flags);

    // --- initialisation
    InitWindow(WIDTH, HEIGHT, TextFormat("Raylib %s - %s", RAYLIB_VERSION, TITLE));
    InitAudioDevice();
    SetExitKey(KEY_NULL);

    // --- input and camera
    Camera3D camera = camera_init();
    capture_mouse(true);

    bool running = true;
    
    while (running) {
        running ^= WindowShouldClose();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw 3D
        BeginMode3D(camera);
        camera_look(&camera);
        DrawGrid(1000, 10.0);

        EndMode3D();

        // Draw 2D on top

        DrawFPS(0, 0);
        EndDrawing();
    }

    capture_mouse(false);

    // Unloading resources...
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
