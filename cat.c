#include <stdlib.h>
#include <stdio.h>
void cat(const char *path){
    FILE *f = fopen(path, "r");
    if (f == NULL){
        perror("Error opening file");
        exit(1);
    }
    else{
        char c;
        while ((c = fgetc(f)) != EOF){
            putchar(c);
        }
    }
    exit(0);
}