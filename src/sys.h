#pragma once

#include "raylib.h"

#define _STRINGIFY(X) #X
#define STR(X) _STRINGIFY(X)

typedef struct {
    int id;
    int width, height;
    int refresh;
    const char* title;
} Monitor;

Monitor monitor_get_info() {
    Monitor m;
    m.id = GetCurrentMonitor();
    m.title = GetMonitorName(m.id);
    m.width = GetMonitorWidth(m.id);    
    m.height = GetMonitorHeight(m.id);
    m.refresh = GetMonitorRefreshRate(m.id);

    return m;
}

