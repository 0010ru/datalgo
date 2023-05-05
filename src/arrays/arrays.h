#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>



struct Array {
    int64_t* data;
    size_t size;
    size_t capacity;
    size_t _chunksize;
};


ssize_t push(struct Array* arr, int64_t value) {
    if (arr == NULL) {
        fprintf(stderr, "[push_back] Array pointer is null");
        return EXIT_FAILURE;
    }
    if (arr->size == arr->capacity) {
        arr->capacity += arr->_chunksize;
        int64_t* tmp = realloc(arr->data, arr->capacity * sizeof(int64_t));
        if (tmp == NULL) {
           fprintf(stderr, "[realloc] Error while reallocating memory");
           return EXIT_FAILURE;
        }
        arr->data = tmp;
    }
    else if (arr->data == NULL) {
        arr->data = malloc(arr->capacity * sizeof(int64_t));
        if (arr->data == NULL) {
            perror("[malloc] Error while allocating memory");
            return EXIT_FAILURE;
        }
    }
    arr->data[arr->size++] = value;
    return EXIT_SUCCESS;
}


ssize_t display(const char* name, struct Array* arr) {
    printf("%s = [", name);
    for (size_t i = 0; i < arr->size; i++) {
        if (i < arr->size - 1) printf("%ld, ", arr->data[i]);
        else printf("%ld", arr->data[i]);
    }
    printf("]\n");
    return EXIT_SUCCESS;
}


bool is_it_out_of_range(struct Array* arr, ssize_t index) {
    return index < 0 || index >= (ssize_t) arr->size;
}


ssize_t get(struct Array* arr, ssize_t index, int64_t* value) {
    if (index < 0) index = arr->size + index;
    if (!is_it_out_of_range(arr, index)) {
        *value = arr->data[index];
    } else {
        fprintf(stderr, "[get] Index out of range: %ld\n", index);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


ssize_t swap(struct Array* arr, ssize_t index1, ssize_t index2) {
    if (index1 < 0) index1 = arr->size + index1;
    if (index2 < 0) index2 = arr->size + index2;
    if (!is_it_out_of_range(arr, index1) || !is_it_out_of_range(arr, index2)) {
        int64_t temp = arr->data[index1];
        arr->data[index1] = arr->data[index2];
        arr->data[index2] = temp;
    } else {
        fprintf(stderr, "[get] Index out of range index1=%ld or index2=%ld\n", index1, index2);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


/*
Sorts an array of integers using the insertion sort algorithm.

@param arr Pointer to an Array structure representing the array.
@return Return code of the function.

The insertion sort algorithm involves iterating through the array from the second element to the end. At each iteration, we take the element at the current position and compare it with the previous elements. If the previous element is greater than the current one, we shift it to the right by one position. We continue to shift elements until we find an element that is less than or equal to the current one. Then we insert the current element at the found position.

The time complexity of the algorithm is O(n^2) in the worst case and O(n) in the best case when the array is already sorted. The space complexity of the algorithm is O(1), since we do not use additional memory to store the elements.

Illustration:

Sart state - [9, 8, 7, 6, 4, 5]

1. [8, 9, 7, 6, 4, 5]
2. [7, 8, 9, 6, 4, 5]
3. [6, 7, 8, 9, 4, 5]
4. [4, 6, 7, 8, 9, 5]
5. [4, 5, 6, 7, 8, 9]

*/
ssize_t sort_insertion(struct Array* arr) {
    size_t i, j;
    int64_t x;
    for (i = 1; i < arr->size; i++) {
        x = arr->data[i];
        j = i;

        while(j > 0 && arr->data[j-1] > x) {
            arr->data[j] = arr->data[j-1];
            j--;
        }
        arr->data[j] = x;
    }
    return EXIT_SUCCESS;
}


#endif
