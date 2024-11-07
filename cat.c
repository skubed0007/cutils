#include <stdlib.h>
#include <stdio.h>

/**
 * print_file_contents - Prints the contents of a file to standard output.
 *                       The file is read in bulk for efficiency.
 *
 * @file_path: The path to the file to be printed.
 */
void print_file_contents(const char *file_path) {
    FILE *file = fopen(file_path, "r");  // Open the file in read mode
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    } else {
        const size_t buffer_size = 1024;  // Buffer size for reading the file in chunks
        char buffer[buffer_size];  // Buffer to hold chunks of file content

        size_t bytes_read;
        // Read the file in chunks and write to stdout until end of file
        while ((bytes_read = fread(buffer, 1, buffer_size, file)) > 0) {
            fwrite(buffer, 1, bytes_read, stdout);  // Write the chunk to stdout
        }
    }
    fclose(file);  // Close the file when done
    exit(0);  // Exit the program
}
