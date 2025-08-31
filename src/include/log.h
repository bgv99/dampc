#pragma once

typedef enum {
    ERR = 0,
    WARN = 1,
    INFO = 2
} LogLevel;

void _log(LogLevel, char *, ...);