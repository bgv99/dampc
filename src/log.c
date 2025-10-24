#include "include/log.h"

char *log_typeToStr(LogType type) {
    switch(type) {
        case EXPECTED_SEMICOLON: return "Expected a semicolon.";
        case BLANK_SOURCE: return "There is nothing to do.";
        case USAGE_ERROR: return "Usage: dampc <file.damp>";
        case INVALID_SOURCE: return "Invalid Damp source.";
        case EXPECTED_LITERAL: return "Expected a literal.";
        case EXPECTED_RETURN: return "Expected 'return'.";
        default: return NULL;
    }
}

void log_new(Vec *logs, Log log) {
    if(logs) {
        vec_push(logs, &log);
    }
}

void log_flush(Vec *logs) {
    char log_level;
    FILE *stream;
    char *colour_start;
    char *colour_end = "\033[0m";

    for(size_t i = 0; i < vec_length(logs); i++) {
        switch(((Log *) vec_get(logs, i))->level) {
            case ERR:
                log_level = 'x';
                stream = stderr;
                colour_start = "\033[1;31m";

                break;
            case WARN:
                log_level = '!';
                stream = stderr;
                colour_start = "\033[1;33m";

                break;
            case INFO:
                log_level = 'i';
                stream = stdout;
                colour_start = "\033[1;34m";
        }

        fprintf(stream, "%s[ %c ]%s %s\n",
            colour_start,
            log_level,
            colour_end,
            log_typeToStr(((Log *) vec_get(logs, i))->type)
        );
    }

    vec_destroy(logs);
}