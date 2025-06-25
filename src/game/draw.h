#pragma once

#include "raylib.h"
#include "game.h"

void game_draw(game_t* game) {

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw 3D
    // BeginMode2D(camera);

    // EndMode2D();

    // Draw 2D on top

    DrawFPS(0, 0);
    EndDrawing();

}
