#pragma once

#include <stdlib.h>

typedef struct Vec Vec;

Vec *Vec_init(size_t byte_size, unsigned int element_count);
void Vec_push(Vec *vec, void *value);
void Vec_pop(Vec *vec);
void *Vec_get(Vec *vec, unsigned int index);
void Vec_destroy(Vec *vec);
unsigned int Vec_length(Vec *vec);
unsigned int Vec_capacity(Vec *vec);