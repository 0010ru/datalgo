#include <stdio.h>
#include <stdlib.h>

struct Array {
    int* data;
    size_t size;
    size_t capacity;
};

void push_back(struct Array* arr, int value) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        int* tmp = (int*)realloc(arr->data, arr->capacity * sizeof(int));
        if (tmp == NULL) {
            perror("Error while reallocating memory");
            exit(EXIT_FAILURE);
        }
        arr->data = tmp;
    }
    arr->data[arr->size++] = value;
}


int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: too few or too many arguments!\n");
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        fprintf(stderr, "Your input: ");
        for (size_t i = 0; i < (size_t)argc; i++)
            fprintf(stderr, "%s ", argv[i]);
        fprintf(stderr, "\n");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error while opening file");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t line_len = 0;
    ssize_t read;

    struct Array arr;
    arr.size = 0;
    arr.capacity = 52;
    arr.data = (int*)malloc(arr.capacity * sizeof(int));

    // The array is filled with data from the file
    while ((read = getline(&line, &line_len, fp)) != -1) {
        int num = strtol(line, NULL, 10);
        push_back(&arr, num);
    }

    // Print all values
    printf("input data = [");
    for (size_t i = 0; i < (size_t)arr.size; i++) {
        if (i < (size_t)(arr.size - 1)) printf("%d, ", arr.data[i]);
        else printf("%d", arr.data[i]);
    }
    printf("]\n");

    if (ferror(fp)) {
        perror("Error while reading file");
    }

    free(arr.data);
    free(line);
    fclose(fp);
    return EXIT_SUCCESS;
}
