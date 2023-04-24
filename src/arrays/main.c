#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: too few or too many arguments!\n");
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        fprintf(stderr, "Your input: ");
        for (size_t i = 0; i < argc; i++)
            fprintf(stderr, "%s ", argv[i]);
        fprintf(stderr, "\n");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error: can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t line_len = 0;
    ssize_t read;

    while ((read = getline(&line, &line_len, fp)) > 0) {
        int num = strtol(line, NULL, 10);
        printf("%d\n", num);
    }

    if (ferror(fp)) {
        perror("Error while reading file");
    }

    free(line);
    fclose(fp);
    return EXIT_SUCCESS;
}
