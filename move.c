#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

void delete_dir(const char *dir_path) {
    struct dirent *entry;
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Error opening directory for deletion");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            struct stat st;
            if (stat(path, &st) == 0) {
                if (S_ISDIR(st.st_mode)) {
                    delete_dir(path);  // Recursively delete subdirectories
                } else {
                    if (remove(path) == -1) {
                        perror("Failed to remove file");
                    }
                }
            }
        }
    }

    closedir(dir);
    if (rmdir(dir_path) == -1) {
        perror("Failed to remove directory");
    }
}

void mv(const char *src, const char *dst) {
    struct stat st = {0};
    if (stat(dst, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            delete_dir(dst);  // Remove non-empty directory
        } else {
            if (remove(dst) == -1) {
                perror("Cannot remove existing destination");
                exit(1);
            }
        }
    }

    if (rename(src, dst) == -1) {
        perror("Failed to move source to destination");
        exit(1);
    }

    printf("Successfully moved %s to %s\n", src, dst);
}
