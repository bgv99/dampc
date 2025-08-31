#include "include/log.h"
#include "include/lexer.h"
#include <stdio.h>
#include <stdarg.h>

extern char *filename;
extern Token *t;

void _log(LogLevel log_level, char *msg, ...) {
    char *_filename = (filename) ? filename : "dampc";
    va_list arg_list;

    va_start(arg_list, msg);

    switch(log_level) {
        case INFO:
            (t) ? printf("\033[38;5;4m[ i ]\033[0m \033[38;5;8m[%s:%d:%d]\033[0m ", _filename, t->line, t->column) : printf("\033[38;5;4m[ i ]\033[0m \033[38;5;8m[%s]\033[0m ", _filename);
            vprintf(msg, arg_list);
            putchar('\n');

            break;
        case ERR:
            (t) ? printf("\033[38;5;9m[ x ]\033[0m \033[38;5;8m[%s:%d:%d]\033[0m ", _filename, t->line, t->column) : printf("\033[38;5;9m[ x ]\033[0m \033[38;5;8m[%s]\033[0m ", _filename);
            vprintf(msg, arg_list);
            putchar('\n');

            break;
        case WARN:
            (t) ? printf("\033[38;5;3m[ ! ]\033[0m \033[38;5;8m[%s:%d:%d]\033[0m ", _filename, t->line, t->column) : printf("\033[38;5;3m[ ! ]\033[0m \033[38;5;8m[%s]\033[0m ", _filename);
            vprintf(msg, arg_list);
            putchar('\n');
    }

    va_end(arg_list);
}