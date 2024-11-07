#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#else
#include <sys/stat.h>
#endif

void makdir(const char *dir_path, mode_t mode)
{
    if (mkdir(dir_path, mode) == 0)
    {
        printf("Successfully created directory %s\n", dir_path);
    }
    else
    {
        perror("Failed to create directory");
    }
}
