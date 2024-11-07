#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

/**
 * delete_directory - Recursively deletes a directory and all its contents.
 *
 * @dir_path: The path to the directory that should be deleted. The function will
 *            recursively remove all files and subdirectories within the specified
 *            directory before deleting the directory itself.
 *
 * The function attempts to open the specified directory, and iterates through its contents,
 * recursively deleting subdirectories and files. It then removes the empty directory.
 *
 * Example Usage:
 *   delete_directory("/path/to/directory");  // Deletes the specified directory and its contents
 */
void delete_directory(const char *dir_path) {
    struct dirent *entry;
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Error opening directory for deletion");
        return;
    }

    // Iterate through the directory entries
    while ((entry = readdir(dir)) != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            struct stat entry_stat;
            if (stat(full_path, &entry_stat) == 0) {
                if (S_ISDIR(entry_stat.st_mode)) {
                    delete_directory(full_path);  // Recursively delete subdirectories
                } else {
                    if (remove(full_path) == -1) {
                        perror("Failed to remove file");
                    }
                }
            }
        }
    }

    // Close the directory stream and remove the directory
    closedir(dir);
    if (rmdir(dir_path) == -1) {
        perror("Failed to remove directory");
    }
}

/**
 * move_file_or_directory - Moves a file or directory from the source path to the destination path.
 *                           If the destination already exists, it is deleted before the move.
 *
 * @src_path: The path of the source file or directory to be moved.
 * @dst_path: The destination path where the source file or directory should be moved.
 *
 * This function checks if the destination exists and removes it before moving the source. It
 * supports both regular files and directories.
 *
 * Example Usage:
 *   move_file_or_directory("/path/to/source", "/path/to/destination");  // Moves source to destination
 */
void move_file_or_directory(const char *src_path, const char *dst_path) {
    struct stat st = {0};

    // Check if destination exists
    if (stat(dst_path, &st) == 0) {
        // If destination is a directory, remove it and its contents
        if (S_ISDIR(st.st_mode)) {
            delete_directory(dst_path);  // Remove non-empty directory
        } else {
            if (remove(dst_path) == -1) {
                perror("Cannot remove existing destination");
                exit(1);
            }
        }
    }

    // Move the source to the destination
    if (rename(src_path, dst_path) == -1) {
        perror("Failed to move source to destination");
        exit(1);
    }

    printf("Successfully moved %s to %s\n", src_path, dst_path);
}
