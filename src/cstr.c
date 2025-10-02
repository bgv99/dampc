#include "include/cstr.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char* cstr_clone_malloc(const char* src) {
    if (src == NULL) return NULL;

    const size_t char_count = strlen(src) + 1; // +1 to account for null-terminator byte. :)

    const size_t mem_count = char_count * sizeof(char);

    char* new_cstr = malloc(mem_count);
    if (new_cstr == NULL) {
        return NULL;
    }

    memcpy(new_cstr, src, mem_count);

    return new_cstr;
}
