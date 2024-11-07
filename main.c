
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cutils.h"

void prnh()
{
    printf("Usage: cutils <command> <args>\n");
    printf("Commands are :\n");
    printf("    - help (-h) : print this help message\n");
    printf("    - ls (list) <dir> : list files in a directory\n");
    printf("    - cat <file> : print file content\n");
    printf("    - cp <src> <dst> : copy file\n");
    printf("    - mv <src> <dst> : move file\n");
    printf("    - rm <file> : remove file\n");
    printf("    - rmdir <dir> : remove directory\n");
    printf("    - mkdir <dir> : create directory\n");
    printf("    - touch <file> : create file\n");
    printf("    - echo <text|$ENV_VAR|$(command)> : print text or environment variable value or output of command\n");
}
int main(int argc, char const *argv[])
{
    int i;
    if (argc < 2)
    {
        prnh();
        return 0;
    }
    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "h") == 0 || strcmp(argv[i], "help") == 0)
        {
            prnh();
            return 0;
        }
        else if (strcmp(argv[i], "echo") == 0)
        {
            if (i + 1 < argc)
            {
                echo_command(argc, argv, i + 1);
            }
            else
            {
                printf("Error: No argument provided for echo command\n");
            }
            return 0;
        }
        else if (strcmp(argv[i], "ls") == 0 || strcmp(argv[i], "list") == 0)
        {
            if (i + 1 < argc)
            {
                list(argv[i + 1]);
            }
            else
            {
                list(".");
            }
            return 0;
        }
        else if (strcmp(argv[i], "cat") == 0)
        {

            if (argv[i + 1] != NULL)
            {
                cat(argv[i + 1]);
            }
            else
            {
                perror("Error: No file provided for cat command\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "cp") == 0)
        {
            if (argv[i + 1] != NULL && argv[i + 2] != NULL)
            {
                copy(argv[i + 1], argv[i + 2]);
            }
            else
            {
                perror("Error: No source or destination provided for cp command\n");
                return 1;
            }
        }

        else if (strcmp(argv[i], "mv") == 0)
        {
            if (argv[i + 1] != NULL && argv[i + 2] != NULL)
            {
                mv(argv[i + 1], argv[i + 2]);
            }
            else
            {
                perror("Error: No source or destination provided for cp command\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "rm") == 0)
        {
            if (argv[i + 1] != NULL)
            {
                if (remove(argv[i + 1]) == 0)
                {
                    printf("Successfully removed %s\n", argv[i + 1]);
                }
                else
                {
                    perror("Error: Failed to remove file\n");
                    return 1;
                }
            }
            else
            {
                perror("Error: No file provided for rm command\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "rmdir") == 0)
        {
            if (argv[i + 1] != NULL)
            {
                delete_dir(argv[i + 1]);
            }
            else
            {
                perror("Error: No directory provided for rmdir command\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "mkdir") == 0)
        {
            if (argv[i + 1] != NULL){
                makdir(argv[i + 1], 0755);
            }
        }
        else if (strcmp(argv[i],"touch") == 0){
            if (argv[i + 1] != NULL){
                touch(argv[i + 2]);
            }
        }
    }
    return 0;
}
