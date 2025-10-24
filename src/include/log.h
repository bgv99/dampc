#ifndef LOG_H
#define LOG_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "vec.h"

extern Vec *logs;

typedef enum {
    ERR,
    WARN,
    INFO
} LogLevel;

typedef enum {
    EXPECTED_SEMICOLON,
    BLANK_SOURCE,
    USAGE_ERROR,
    INVALID_SOURCE,
    EXPECTED_LITERAL,
    EXPECTED_RETURN
} LogType;

typedef struct {
    LogLevel level;
    LogType type;
} Log;

char *log_typeToStr(LogType type);
void log_new(Vec *logs, Log log);
void log_flush(Vec *logs);

#endif