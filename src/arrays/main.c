#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

struct Array {
    int16_t* data;
    size_t size;
    size_t capacity;
};


void reshuffle(struct Array* arr) {
    if (arr == NULL) {
        fprintf(stderr, "[reshuffle] Array pointer is null");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    for (size_t i = arr->size - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        int16_t temp = arr->data[i];
        arr->data[i] = arr->data[j];
        arr->data[j] = temp;
    }
}


void push_back(struct Array* arr, int16_t value) {
    if (arr == NULL) {
        fprintf(stderr, "[push_back] Array pointer is null");
        exit(EXIT_FAILURE);
    }
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        int16_t* tmp = realloc(arr->data, arr->capacity * sizeof(int16_t));
        if (tmp == NULL) {
           fprintf(stderr, "[realloc] Error while reallocating memory");
            exit(EXIT_FAILURE);
        }
        arr->data = tmp;
    }
    else if (arr->data == NULL) {
        arr->data = malloc(arr->capacity * sizeof(int16_t));
        if (arr->data == NULL) {
            perror("[malloc] Error while allocating memory");
            exit(EXIT_FAILURE);
        }
    }
    arr->data[arr->size++] = value;
}


void display(const char *name, struct Array* arr) {
    printf("%s = [", name);
    for (size_t i = 0; i < arr->size; i++) {
        if (i < arr->size - 1) printf("%hd, ", arr->data[i]);
        else printf("%hd", arr->data[i]);
    }
    printf("]\n");
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: invalid number of arguments!\n");
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("[fopen] Error while opening file");
        return EXIT_FAILURE;
    }

    struct Array arr = { NULL, 0, 64 };
    char* line = NULL;
    size_t line_len = 0;

    ssize_t read;
    while ((read = getline(&line, &line_len, fp)) != -1) {
        int16_t num = 0;
        if (sscanf(line, "%hd", &num) == 1) {
            push_back(&arr, num);
        } else {
            fprintf(stderr, "[sscanf] Invalid input: %s\n", line);
            free(line);
            fclose(fp);
            free(arr.data);
            return EXIT_FAILURE;
        }
    }
    free(line);
    fclose(fp);
    display("file data", &arr);

    reshuffle(&arr);
    display("reshuffled", &arr);

    free(arr.data);
    return EXIT_SUCCESS;
}
