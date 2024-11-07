#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cutils.h"

/**
 * print_usage - Prints the usage instructions for the command-line utility.
 *
 * Provides the user with a list of supported commands and their corresponding syntax.
 */
void print_usage() {
    printf("Usage: cutils <command> <args>\n");
    printf("Commands are:\n");
    printf("    - help (-h) : Print this help message\n");
    printf("    - ls (list) <dir> : List files in a directory\n");
    printf("    - cat <file> : Print file content\n");
    printf("    - cp <src> <dst> : Copy file\n");
    printf("    - mv <src> <dst> : Move file\n");
    printf("    - rm <file> : Remove file\n");
    printf("    - rmdir <dir> : Remove directory\n");
    printf("    - mkdir <dir> : Create directory\n");
    printf("    - touch <file> : Create empty file\n");
    printf("    - echo <text|$ENV_VAR|$(command)> : Print text or environment variable value or output of command\n");
}

int main(int argc, char const *argv[]) {
    int i;
    if (argc < 2) {
        print_usage();
        return 0;
    }

    for (i = 1; i < argc; i++) {  // Start from 1 to skip the program name
        if (strcmp(argv[i], "help") == 0 || strcmp(argv[i], "h") == 0) {
            print_usage();
            return 0;
        }
        else if (strcmp(argv[i], "echo") == 0) {
            if (i + 1 < argc) {
                print_command_arguments(argc, argv, i + 1);  // Calling the echo command function
            } else {
                printf("Error: No argument provided for echo command\n");
            }
            return 0;
        }
        else if (strcmp(argv[i], "ls") == 0 || strcmp(argv[i], "list") == 0) {
            if (i + 1 < argc) {
                list_directory_contents(argv[i + 1]);
            } else {
                list_directory_contents(".");  // Default to current directory
            }
            return 0;
        }
        else if (strcmp(argv[i], "cat") == 0) {
            if (i + 1 < argc) {
                print_file_contents(argv[i + 1]);
            } else {
                perror("Error: No file provided for cat command\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "cp") == 0) {
            if (i + 2 < argc) {
                copy_file(argv[i + 1], argv[i + 2]);
            } else {
                perror("Error: No source or destination provided for cp command\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "mv") == 0) {
            if (i + 2 < argc) {
                move_file_or_directory(argv[i + 1], argv[i + 2]);
            } else {
                perror("Error: No source or destination provided for mv command\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "rm") == 0) {
            if (i + 1 < argc) {
                remove(argv[i + 1]);
            } else {
                perror("Error: No file provided for rm command\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "rmdir") == 0) {
            if (i + 1 < argc) {
                delete_directory(argv[i + 1]);
            } else {
                perror("Error: No directory provided for rmdir command\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "mkdir") == 0) {
            if (i + 1 < argc) {
                create_directory(argv[i + 1], 0755);
            } else {
                perror("Error: No directory provided for mkdir command\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "touch") == 0) {
            if (i + 1 < argc) {
                create_file_if_not_exists(argv[i + 1]);
            } else {
                perror("Error: No file provided for touch command\n");
                return 1;
            }
        } else {
            printf("Error: Unknown command %s\n", argv[i]);
            print_usage();
            return 1;
        }
    }

    return 0;
}
