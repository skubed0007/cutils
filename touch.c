#include <stdio.h>
#include <stdlib.h>

/**
 * create_file_if_not_exists - Creates a new empty file if it does not already exist.
 *                             If the file already exists, an error message is printed.
 *
 * @file_path: The path to the file that should be created.
 *
 * This function attempts to create a new file at the specified path. If the file already
 * exists, it will print an error message and return. If the file creation fails for any reason,
 * it will print an error message and exit the program.
 *
 * Example Usage:
 *   create_file_if_not_exists("/path/to/file.txt");  // Creates file if not already existing
 */
void create_file_if_not_exists(const char *file_path) {
    // Try to open the file in read mode to check if it already exists
    FILE *fp = fopen(file_path, "r");
    if (fp != NULL) {
        // If the file exists, close it and report
        fclose(fp);
        perror("File already exists");
        return;
    }

    // Try to create a new file by opening it in write mode
    fp = fopen(file_path, "w");
    if (fp == NULL) {
        // If file creation fails, print the error and exit
        perror("Failed to create file");
        exit(1);
    }

    // Close the file after creation
    fclose(fp);

    // Print success message
    printf("Successfully created file: %s\n", file_path);
}
