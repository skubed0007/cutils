# cutils : Re-Implementation of core-utils in C

This is a collection of utility functions that I use in my projects. The functions are implemented in C and are designed to be portable across different platforms and compilers.

## Functions

### echo_command

Prints the command line arguments to standard output. If an argument starts with '$', it is treated as an environment variable, and its value is printed. Otherwise, the argument itself is printed.

#### Parameters

- `argc`: The total number of arguments passed to the command, including the program name.
- `argv`: An array of strings representing the arguments passed to the command.
- `start_index`: The index from which to start processing the arguments. This allows skipping the command name and processing only the user-provided arguments.

#### Example Usage
```bash
cutils echo hello 
cutils echo $HOME
cutils echo $PATH
```
### ls

Lists the files and directories in the specified directory. If the directory does not exist, the function prints an error message and exits.

#### Parameters

- `path`: The path of the directory to list.

#### Example Usage

```bash
cutils ls /home/user
```
### touch

Creates a file with the specified path. If the file already exists, the function prints an error message and exits.

#### Parameters

- `path`: The path of the file to create.

#### Example Usage

```bash
cutils touch /home/user/some_file.txt
```

### cat

reads from file and prints the contents to standard output. If the file does not exist, the function prints an error message and exits.

#### Parameters

- `path`: The path of the file to read.

#### Example Usage

```bash
cutils cat /home/user/some_file.txt
```

### copy

Copies a file from one location to another. If the source file does not exist, the function prints an error message and exits.

#### Parameters

- `source_path`: The path of the file to copy.
- `destination_path`: The path of the destination file.

#### Example Usage

```bash
cutils cp /home/user/some_file.txt /home/user/new_file.txt
```

### move

Moves a file from one location to another. If the source file does not exist, the function prints an error message and exits.

#### Parameters

- `source_path`: The path of the file to move.
- `destination_path`: The path of the destination file.

#### Example Usage

### mkdir

Creates a directory with the specified path. If the directory already exists, the function prints an error message and exits.

#### Parameters

- `path`: The path of the directory to create.directory. Default value is.

#### Example Usage
```bash
cutils mkdir /home/user/some_dir
```

### rm
#### removes the specified file
```bash
cutils rm ./tst.txt
```

### rmdir
#### removes the specified directory
```bash
cutils rmdir ./tst_dir
```
## License

This project is licensed under the GPL License. See the [LICENSE](LICENSE) file for details.