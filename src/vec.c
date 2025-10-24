#include "include/vec.h"

typedef struct Vec {
    size_t length;
    size_t capacity;
    void *elements;
    size_t element_size;
} Vec;

Vec *vec_init(size_t byte_size, uint32_t element_count) {
    Vec *initial_alloc = malloc(sizeof(Vec));

    initial_alloc->elements = malloc(byte_size * element_count);

    if(initial_alloc == NULL || initial_alloc->elements == NULL) {
        return NULL;
    }

    initial_alloc->length = 0;
    initial_alloc->capacity = element_count;
    initial_alloc->element_size = byte_size;

    return initial_alloc;
}

void vec_push(Vec *vec, void *value) {
    if(!vec) {
        return;
    }

    if(vec->length == vec->capacity) {
        vec->elements = realloc(vec->elements, (vec->capacity + 1) * vec->element_size);

        if(vec->elements == NULL) {
            return;
        }

        vec->capacity++;
    }

    memcpy(((int8_t *) vec->elements + (vec->length * vec->element_size)), value, vec->element_size);

    vec->length++;
}

void vec_pop(Vec *vec) {
    if(!vec || vec->length == 0) {
        return;
    }

    vec->length--;
}

void *vec_get(Vec *vec, size_t index) {
    if(index >= vec->length) {
        return NULL;
    }

    return (void *) ((int8_t *) vec->elements + (index * vec->element_size));
}

void vec_destroy(Vec *vec) {
    if(!vec) {
        return;
    }

    free(vec->elements);
    free(vec);
}

size_t vec_length(Vec *vec) {
    return vec->length;
}

size_t vec_capacity(Vec *vec) {
    return vec->capacity;
}