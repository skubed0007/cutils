#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#else
#include <sys/stat.h>
#endif

void file(const char *src, const char *dst);
void dir(const char *src, const char *dst);
void dhlp(const char *src, const char *dst);

void file(const char *src, const char *dst) {
    FILE *sf = fopen(src, "r");
    if (!sf) {
        perror("fopen (source)");
        return;
    }
    
    FILE *twf = fopen(dst, "w");
    if (!twf) {
        perror("fopen (destination)");
        fclose(sf);
        return;
    }

    char sfc;
    while ((sfc = fgetc(sf)) != EOF) {
        fputc(sfc, twf);
    }
    
    fclose(sf);
    fclose(twf);
}

void dhlp(const char *src, const char *dst) {
    dir(src, dst);
}

void dir(const char *src, const char *dst) {
    struct stat st = {0};
    if (stat(dst, &st) == -1 && mkdir(dst, 0700) == -1) {
        perror("mkdir");
        return;
    }

    DIR *dir = opendir(src);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char src_path[1024], dst_path[1024];
        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        snprintf(dst_path, sizeof(dst_path), "%s/%s", dst, entry->d_name);

        struct stat st;
        if (stat(src_path, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                dhlp(src_path, dst_path);
            } else if (S_ISREG(st.st_mode)) {
                file(src_path, dst_path);
            }
        }
    }
    closedir(dir);
}

void copy(const char *src, const char *dst) {
    struct stat st = {0};
    if (stat(src, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            dir(src, dst);
        } else if (S_ISREG(st.st_mode)) {
            file(src, dst);
        }
    } else {
        perror("stat");
    }
}
