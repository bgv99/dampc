#include "include/vec.h"
#include <stdio.h>
#include <memory.h>

typedef struct Vec {
    unsigned int length;
    unsigned int capacity;
    void *elements;
    size_t element_size;
} Vec;

Vec *Vec_init(size_t byte_size, unsigned int element_count) {
    Vec *initial_alloc = malloc(sizeof(Vec));

    initial_alloc->elements = malloc(byte_size * element_count);

    if(initial_alloc == NULL || initial_alloc->elements == NULL) {
        printf("vecc: allocation failed during initialisation (null)\n");
        exit(EXIT_FAILURE);
    }

    initial_alloc->length = 0;
    initial_alloc->capacity = element_count;
    initial_alloc->element_size = byte_size;

    return initial_alloc;
}

void Vec_push(Vec *vec, void *value) {
    if(vec->length == vec->capacity) {
        vec->elements = realloc(vec->elements, (vec->capacity + 1) * vec->element_size);

        if(vec->elements == NULL) {
            printf("vecc: reallocation failed while pushing an element\n");
            Vec_destroy(vec);
            exit(EXIT_FAILURE);
        }

        vec->capacity++;
    }

    memcpy(((char *) vec->elements + (vec->length * vec->element_size)), value, vec->element_size);

    vec->length++;
}

void Vec_pop(Vec *vec) {
    if(vec->length == 0) {
        return;
    }

    vec->length--;
}

void *Vec_get(Vec *vec, unsigned int index) {
    if(index >= vec->length) {
        return NULL;
    }

    return (void *) ((char *) vec->elements + (index * vec->element_size));
}

void Vec_destroy(Vec *vec) {
    free(vec->elements);
    free(vec);
}

unsigned int Vec_length(Vec *vec) {
    return vec->length;
}

unsigned int Vec_capacity(Vec *vec) {
    return vec->capacity;
}