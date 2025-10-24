#ifndef VEC_H
#define VEC_H

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <stdint.h>

typedef struct Vec Vec;

Vec *vec_init(size_t byte_size, uint32_t element_count);
void vec_push(Vec *vec, void *value);
void vec_pop(Vec *vec);
void *vec_get(Vec *vec, size_t index);
void vec_destroy(Vec *vec);
size_t vec_length(Vec *vec);
size_t vec_capacity(Vec *vec);

#endif