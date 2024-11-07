#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

void echo_command(int argc, const char *argv[], int start_index);
void list(const char *path);
void cat(const char *path);
void copy(const char *src, const char *dst);
void dhlp(const char *src, const char *dst);
void file(const char *src, const char *dst);
void dir(const char *src, const char *dst);
void mv(const char *src, const char *dst);
void delete_dir(const char *dir_path);
void makdir(const char *dir_path, mode_t mode);
void touch(const char *path);