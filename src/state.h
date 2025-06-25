#include "raylib.h"
#include "scenes/scene.c"
#include <stdbool.h>

// The game state
typedef struct {
    Scene scene;
    bool running;
} GState;


