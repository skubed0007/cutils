#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * print_command_arguments - Prints the command line arguments to standard output.
 *                            If an argument starts with '$', it is treated as an environment
 *                            variable, and its value is printed. Otherwise, the argument itself
 *                            is printed.
 *
 * @argc: The total number of arguments passed to the command, including the program name.
 * @argv: An array of strings representing the arguments passed to the command.
 * @start_index: The index from which to start processing the arguments. This allows
 *               skipping the command name and processing only the user-provided arguments.
 *
 * The function iterates over the command-line arguments starting from `start_index`, printing
 * each argument. If the argument starts with a dollar sign (`$`), it tries to treat it as an
 * environment variable and prints its value. If the environment variable is not found, it prints
 * an error message. Otherwise, it prints the argument as is.
 * 
 * The function ensures that there is a space between the printed arguments, but no trailing space
 * is added after the last argument.
 *
 * Example Usage:
 *   // Suppose the environment variable "HOME" exists:
 *   print_command_arguments(3, argv, 1);  // Output: /home/user some_text
 */
void print_command_arguments(int argc, const char *argv[], int start_index) {
    // Iterate through the arguments starting from start_index
    for (int i = start_index; i < argc; i++) {
        // Check if the argument starts with '$', indicating an environment variable
        if (argv[i][0] == '$') {
            // Skip the '$' character to get the environment variable name
            const char *env_var_name = argv[i] + 1;
            const char *env_var_value = getenv(env_var_name);  // Get the environment variable value

            // If the environment variable is found, print its value
            if (env_var_value) {
                printf("%s", env_var_value);
            } else {
                // If the environment variable is not found, print an error message
                printf("Environment variable %s not found", env_var_name);
            }
        } else {
            // If the argument is not an environment variable, print it as is
            printf("%s", argv[i]);
        }

        // Print a space after each argument except the last one
        if (i < argc - 1) {
            printf(" ");
        }
    }

    // Print a newline at the end of the output
    printf("\n");
}
