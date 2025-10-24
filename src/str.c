#include "include/str.h"

char *str_clone(char *str) {
    if(!str) {
        return NULL;
    }

    size_t slen = strlen(str);
    char *_str = malloc(sizeof(char) * slen + 1);

    if(!_str) {
        return NULL;
    }

    for(size_t i = 0; i < slen; i++) {
        _str[i] = str[i];
    }

    _str[slen] = '\0';

    return _str;
}