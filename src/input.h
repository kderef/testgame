#pragma once

#include "raylib.h"
#include <stdbool.h>

void capture_mouse(bool capture) {
    if (capture) DisableCursor();
    else EnableCursor();
}
