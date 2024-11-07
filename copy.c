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

void copy_directory(const char *src_path, const char *dst_path);

/**
 * copy_file - Copies a file from the source path to the destination path.
 *            The source file is read in bulk and written to the destination file.
 *
 * @src_path: The source file path.
 * @dst_path: The destination file path.
 */
void copy_file(const char *src_path, const char *dst_path) {
    FILE *source_file = fopen(src_path, "rb");  // Open source file for reading in binary mode
    if (!source_file) {
        perror("Error opening source file");
        return;
    }
    
    FILE *destination_file = fopen(dst_path, "wb");  // Open destination file for writing in binary mode
    if (!destination_file) {
        perror("Error opening destination file");
        fclose(source_file);
        return;
    }

    char buffer[8192];  // Buffer to read and write data in bulk (8KB)
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {  // Read data from source file in bulk
        fwrite(buffer, 1, bytes_read, destination_file);  // Write data to the destination file
    }
    
    fclose(source_file);
    fclose(destination_file);
}

/**
 * copy_directory_contents - A helper function for copying the contents of a directory.
 *                            It recursively copies the contents from the source directory to the destination directory.
 *
 * @src_dir: The source directory path.
 * @dst_dir: The destination directory path.
 */
void copy_directory_contents(const char *src_dir, const char *dst_dir) {
    copy_directory(src_dir, dst_dir);  // Call the `copy_directory` function to copy directory contents
}

/**
 * copy_directory - Copies the contents of a directory from the source path to the destination path.
 *                  It creates the destination directory if it doesn't exist and copies files and subdirectories.
 *
 * @src_dir: The source directory path.
 * @dst_dir: The destination directory path.
 */
void copy_directory(const char *src_dir, const char *dst_dir) {
    struct stat dir_stat = {0};
    
    // Create the destination directory if it doesn't exist
    if (stat(dst_dir, &dir_stat) == -1 && mkdir(dst_dir, 0700) == -1) {
        perror("Error creating destination directory");
        return;
    }

    DIR *dir = opendir(src_dir);  // Open the source directory
    if (!dir) {
        perror("Error opening source directory");
        return;
    }

    struct dirent *entry;
    // Iterate through the directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip the current (.) and parent (..) directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char src_path[1024], dst_path[1024];
        snprintf(src_path, sizeof(src_path), "%s/%s", src_dir, entry->d_name);  // Full source path
        snprintf(dst_path, sizeof(dst_path), "%s/%s", dst_dir, entry->d_name);  // Full destination path

        struct stat entry_stat;
        if (stat(src_path, &entry_stat) == 0) {  // Check if the source path exists
            // If it's a directory, recursively copy its contents
            if (S_ISDIR(entry_stat.st_mode)) {
                copy_directory_contents(src_path, dst_path);
            } 
            // If it's a regular file, copy it
            else if (S_ISREG(entry_stat.st_mode)) {
                copy_file(src_path, dst_path);
            }
        }
    }
    closedir(dir);
}

/**
 * copy - Copies a file or a directory from the source path to the destination path.
 *        It checks whether the source is a file or a directory and calls the appropriate function (`copy_file` or `copy_directory`).
 *
 * @src_path: The source file or directory path.
 * @dst_path: The destination file or directory path.
 */
void copy(const char *src_path, const char *dst_path) {
    struct stat src_stat = {0};
    
    // Check if the source exists and determine whether it's a file or directory
    if (stat(src_path, &src_stat) == 0) {
        if (S_ISDIR(src_stat.st_mode)) {  // If source is a directory, copy it
            copy_directory(src_path, dst_path);
        } else if (S_ISREG(src_stat.st_mode)) {  // If source is a file, copy it
            copy_file(src_path, dst_path);
        }
    } else {
        perror("Error checking source path");
    }
}
