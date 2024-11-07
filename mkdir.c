#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#else
#include <sys/stat.h>
#endif

/**
 * create_directory - Creates a new directory at the specified path with the given mode.
 *
 * @dir_path: The path where the directory should be created. This can be either a relative or
 *            absolute path.
 * @mode: The permissions to set for the new directory. This parameter is platform-dependent
 *        (e.g., 0755 for Unix-like systems).
 *
 * The function attempts to create the directory at the specified path. If the directory is
 * created successfully, a success message is printed. If the creation fails, an error message
 * is printed using `perror`.
 *
 * Example Usage:
 *   create_directory("/path/to/new/dir", 0755);  // Creates a directory with the specified mode
 */
void create_directory(const char *dir_path, mode_t mode) {
    // Attempt to create the directory at the specified path
    if (mkdir(dir_path, mode) == 0) {
        // Print success message if directory is created
        printf("Successfully created directory: %s\n", dir_path);
    } else {
        // Print error message if directory creation fails
        perror("Failed to create directory");
    }
}
