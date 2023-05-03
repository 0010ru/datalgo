#include "arrays.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: invalid number of arguments!\n");
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("[fopen] Error while opening file");
        return EXIT_FAILURE;
    }

    struct Array arr = { NULL, 0, 64, 64 };
    char* line = NULL;
    size_t line_len = 0;

    ssize_t read;
    while ((read = getline(&line, &line_len, fp)) != -1) {
        int64_t num = 0;
        if (sscanf(line, "%ld", &num) == 1) {
            ssize_t res = push(&arr, num);
            if (res != EXIT_SUCCESS) return EXIT_FAILURE;
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
    printf("\n");

    int64_t last_element = 0;
    ssize_t res = get(&arr, -1, &last_element);
    if (res != EXIT_SUCCESS) return EXIT_FAILURE;
    printf("last element = %ld\n", last_element);
    printf("\n");

    swap(&arr, -1, -2);
    display("swaped -1 and -2 = ", &arr);
    printf("\n");

    sort_insertion(&arr);
    display("sorted", &arr);
    printf("\n");

    free(arr.data);
    return EXIT_SUCCESS;
}
