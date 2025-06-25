#pragma once

//! logging

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>

#include "raylib.h"

#define LOG_FILENAME "log.txt"

static bool log_to_file = true;
static FILE* log_file = NULL;

// logging macros
#define info(FMT, ...) TraceLog(LOG_INFO, FMT, ##__VA_ARGS__)
#define warn(FMT, ...) TraceLog(LOG_WARNING, FMT, ##__VA_ARGS__)
#define error(FMT, ...) TraceLog(LOG_ERROR, FMT, ##__VA_ARGS__)
#define fatal(FMT, ...) TraceLog(LOG_FATAL, FMT, ##__VA_ARGS__)
#define trace(FMT, ...) TraceLog(LOG_TRACE, FMT, ##__VA_ARGS__)
#define debug(FMT, ...) TraceLog(LOG_DEBUG, "\033[4m" STR(__FILE_NAME__) "@" STR(__LINE__) "\033[24m: " FMT, ##__VA_ARGS__)

struct LogLevelData {
    const char* prefix;
    const char* color; // \033[91m
};

static const struct LogLevelData LOG_LEVEL_DATA[] = {
    // Not applicable
    [LOG_ALL]     = {"", ""},
    [LOG_NONE]    = {"", ""},
    
    [LOG_TRACE]   = {"TRACE: ", "\033[35m"},
    [LOG_DEBUG]   = {"DEBUG: ", "\033[95m"},
    [LOG_INFO]    = {"INFO: ", "\033[92m"},
    [LOG_WARNING] = {"WARNING: ", "\033[93m"},
    [LOG_ERROR]   = {"ERROR: ", "\033[91m"},
    [LOG_FATAL]   = {"FATAL: ", "\033[91m\033[1m"},
};

errno_t log_open_file() {
    if (log_file || !log_to_file) return 0; // already opened / don't enable logging to file
    
    // try open file
    log_file = fopen(LOG_FILENAME, "w");
    if (log_file == NULL) return errno;

    return 0;
}

void log_close() {
    info("Closing log.");
    
    if (log_file) fclose(log_file);
}

// void (*TraceLogCallback)(int logLevel, const char *text, va_list args);
void rl_log_callback_func(int log_level, const char* text, va_list args) {
    // 1. Get prefix to print
    static struct LogLevelData data;
    
    data = LOG_LEVEL_DATA[log_level];
    
    // 2. print to console
    if (*data.prefix)
        printf("%s%s\033[0m", data.color, data.prefix);
    
    vprintf(text, args);
    putchar('\n');

    // 3. Print to file
    if (log_file && log_to_file) {
        if (*data.prefix)
            fputs(data.prefix, log_file);
        
        vfprintf(log_file, text, args);
        fputc('\n', log_file);
    }
}
static TraceLogCallback rl_log_callback = rl_log_callback_func;

void log_set_minimum_level(int level) {
    SetTraceLogLevel(level);
}
