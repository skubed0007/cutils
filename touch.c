#include <stdio.h>
#include <stdlib.h>

void touch(const char *path) {
    FILE *fp = fopen(path, "r");
    if (fp != NULL) {
        fclose(fp);
        perror("File already exists");
        return;
    }

    fp = fopen(path, "w");
    if (fp == NULL) {
        perror("Failed to create file");
        exit(1);
    }
    fclose(fp);
    printf("Successfully created file %s\n", path);
}
