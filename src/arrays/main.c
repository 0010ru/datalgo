#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Array {
    int16_t* data;
    size_t size;
    size_t capacity;
};

void push_back(struct Array* arr, int16_t value) {
    if (arr == NULL) {
        perror("Array pointer is null");
        exit(EXIT_FAILURE);
    }
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        int16_t* tmp = realloc(arr->data, arr->capacity * sizeof(int16_t));
        if (tmp == NULL) {
            perror("Error while reallocating memory");
            exit(EXIT_FAILURE);
        }
        arr->data = tmp;
    }
    arr->data[arr->size++] = value;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: invalid number of arguments!\n");
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error while opening file");
        return EXIT_FAILURE;
    }

    struct Array arr = {NULL, 0, 64};
    arr.data = malloc(arr.capacity * sizeof(int16_t));
    if (arr.data == NULL) {
        perror("Error while allocating memory");
        fclose(fp);
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t line_len = 0;

    // Fill the array with data from the file
    ssize_t read;
    while ((read = getline(&line, &line_len, fp)) != -1) {
        int16_t num = 0;
        if (sscanf(line, "%hd", &num) == 1) {
            push_back(&arr, num);
        } else {
            fprintf(stderr, "Invalid input: %s\n", line);
            free(line);
            fclose(fp);
            free(arr.data);
            return EXIT_FAILURE;
        }
    }
    free(line);
    fclose(fp);

    // Print all values
    printf("Input data = [");
    for (size_t i = 0; i < arr.size; i++) {
        if (i < arr.size - 1) printf("%hd, ", arr.data[i]);
        else printf("%hd", arr.data[i]);
    }
    printf("]\n");
    free(arr.data);

    return EXIT_SUCCESS;
}
