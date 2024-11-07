#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/**
 * list_directory_contents - Lists the contents of a specified directory, identifying
 *                            folders, regular files, and other file types.
 *
 * @directory_path: The path to the directory whose contents are to be listed. This can
 *                  be either a relative or absolute path.
 *
 * The function opens the specified directory, iterates through each entry (skipping
 * the special `.` and `..` directories), checks the type of each entry (folder, regular
 * file, or other), and prints the appropriate information to the console.
 *
 * If an error occurs while opening the directory or reading a specific entry, an error
 * message will be printed to `stderr`.
 *
 * Example Usage:
 *   list_directory_contents("/home/user");  // Lists the contents of the directory /home/user
 */
void list_directory_contents(const char *directory_path) {
    // Open the directory at the specified path
    DIR *directory = opendir(directory_path);
    struct dirent *entry;

    // Check if the directory was successfully opened
    if (directory == NULL) {
        // Print error message if directory could not be opened
        perror("Error opening directory");
        return;
    }

    // Iterate through each directory entry
    while ((entry = readdir(directory)) != NULL) {
        // Skip the special entries for current directory (.) and parent directory (..)
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;  // Skip to the next iteration
        }

        // Construct the full path of the entry by combining the directory path and entry name
        char full_entry_path[1024];
        snprintf(full_entry_path, sizeof(full_entry_path), "%s/%s", directory_path, entry->d_name);

        // Use stat() to get detailed information about the file or directory
        struct stat entry_stat;
        if (stat(full_entry_path, &entry_stat) == -1) {
            // If stat() fails, print the error and continue to the next entry
            perror("Error getting file status");
            continue;
        }

        // Check if the entry is a directory
        if (S_ISDIR(entry_stat.st_mode)) {
            printf("Folder: %s\n", entry->d_name);  // Print folder info
        }
        // Check if the entry is a regular file
        else if (S_ISREG(entry_stat.st_mode)) {
            printf("File: %s\n", entry->d_name);    // Print file info
        }
        // Handle other types of entries (symbolic links, character devices, etc.)
        else {
            printf("Other: %s\n", entry->d_name);   // Print other type info
        }
    }

    // Close the directory stream
    closedir(directory);
}
