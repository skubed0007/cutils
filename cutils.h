#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * print_echo_arguments - Prints command-line arguments, handling environment variables.
 *
 * @argc: The total number of arguments passed to the command, including the program name.
 * @argv: An array of strings representing the arguments passed to the command.
 * @start_index: The index from which to start processing the arguments.
 */
void print_command_arguments(int argc, const char *argv[], int start_index);

/**
 * list_directory_contents - Lists the contents of a specified directory with detailed file type identification.
 *
 * @path: The path to the directory whose contents are to be listed.
 */
void list_directory_contents(const char *path);

/**
 * display_file_contents - Displays the contents of a file.
 *
 * @path: The path to the file to be displayed.
 */
void print_file_contents(const char *path);

/**
 * copy_file - Copies a file from the source to the destination.
 *
 * @src: The source file path.
 * @dst: The destination file path.
 */
void copy_file(const char *src, const char *dst);

/**
 * copy_directory - Copies the contents of a directory from the source to the destination.
 *
 * @src: The source directory path.
 * @dst: The destination directory path.
 */
void copy_directory(const char *src, const char *dst);

/**
 * create_directory - Creates a directory at the specified path.
 *
 * @dir_path: The path to the directory to be created.
 * @mode: The permissions for the new directory.
 */
void create_directory(const char *dir_path, mode_t mode);

/**
 * move_file_or_directory - Moves a file or directory from the source to the destination.
 *
 * @src: The source path.
 * @dst: The destination path.
 */
void move_file_or_directory(const char *src, const char *dst);

/**
 * delete_directory_recursively - Deletes a directory and its contents recursively.
 *
 * @dir_path: The path to the directory to be deleted.
 */
void delete_directory(const char *dir_path);

/**
 * create_empty_file - Creates an empty file at the specified path if it doesn't already exist.
 *
 * @path: The path to the file to be created.
 */
void create_file_if_not_exists(const char *path);
