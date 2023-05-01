#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


struct Array {
    int16_t* data;
    size_t size;
    size_t capacity;
    size_t _chunksize;
};


ssize_t push(struct Array* arr, int16_t value) {
    if (arr == NULL) {
        fprintf(stderr, "[push_back] Array pointer is null");
        return EXIT_FAILURE;
    }
    if (arr->size == arr->capacity) {
        arr->capacity += arr->_chunksize;
        int16_t* tmp = realloc(arr->data, arr->capacity * sizeof(int16_t));
        if (tmp == NULL) {
           fprintf(stderr, "[realloc] Error while reallocating memory");
           return EXIT_FAILURE;
        }
        arr->data = tmp;
    }
    else if (arr->data == NULL) {
        arr->data = malloc(arr->capacity * sizeof(int16_t));
        if (arr->data == NULL) {
            perror("[malloc] Error while allocating memory");
            return EXIT_FAILURE;
        }
    }
    arr->data[arr->size++] = value;
    return EXIT_SUCCESS;
}


ssize_t display(const char *name, struct Array* arr) {
    printf("%s = [", name);
    for (size_t i = 0; i < arr->size; i++) {
        if (i < arr->size - 1) printf("%hd, ", arr->data[i]);
        else printf("%hd", arr->data[i]);
    }
    printf("]\n");
    return EXIT_SUCCESS;
}

ssize_t get(struct Array* arr, const ssize_t index, int16_t *value) {
    if (index >= 0 && index < (ssize_t) arr->size) {
        *value = arr->data[index];
    } else if (index < 0 && -index <= (ssize_t) arr->size) {
        *value = arr->data[arr->size + index];
    } else {
        fprintf(stderr, "[get] Index out of range: %zd\n", index);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#endif
