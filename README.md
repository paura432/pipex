# pipex

**pipex** is a project that involves implementing a command-line utility to handle pipes and redirection in Unix-like systems. The goal is to create a tool that mimics the behavior of shell pipes (`|`) and redirection (`<`, `>`) to process multiple commands and their outputs.

## Overview

- **Objective**: Implement a command-line utility to execute commands with pipes and redirection.
- **Functionality**: The program should be able to:
  - Execute multiple commands connected by pipes.
  - Handle input and output redirection.
  - Simulate the behavior of shell pipelines.

## Usage

The utility should be invoked with the following command-line syntax:

```bash
./pipex infile "cmd1" "cmd2" ... "cmdN" outfile
```

## Parameters

- **`infile`**: The file to be used as input for the first command.
- **`cmd1`, `cmd2`, ..., `cmdN`**: The commands to be executed in sequence, connected by pipes.
- **`outfile`**: The file where the final output will be written.

## Example

To simulate the command:

```bash
cat input.txt | grep "search_term" | sort > output.txt
```
## Usage

You would use:

```bash
./pipex input.txt "cat" "grep search_term" "sort" output.txt
```
This command reads from `input.txt`, processes it through `cat`, `grep`, and `sort`, and writes the final result to `output.txt`.

## Key Features
- **Pipe Handling**: Connects multiple commands using pipes.
- **Redirection**: Handles input redirection from files and output redirection to files.
- **Forking and Executing**: Uses `fork()` and `exec()` system calls to run commands in separate processes.
- **Error Handling**: Manages errors such as invalid commands, file not found, and permission issues.

## Implementation Details
- **Parsing**: The program parses command-line arguments to extract the input file, commands, and output file.
- **Pipes Setup**: Sets up pipes to connect the standard output of one command to the standard input of the next.
- **Forking**: Creates child processes to execute each command using `fork()`.
- **Redirection**: Redirects input and output as specified by the command-line arguments.
- **Execution**: Uses `execve()` to execute the commands in the child processes.

## Notes
- **Memory Management**: Ensure proper allocation and deallocation of memory to avoid leaks.
- **Error Handling**: Gracefully handle errors, such as invalid commands or file operations.
- **Edge Cases**: Consider edge cases such as empty commands, missing files, and incorrect syntax.

## Additional Features (Optional)
- **Command Validation**: Check the validity of commands and arguments before execution.
- **Interactive Mode**: Add an interactive mode to allow user input directly from the command line.
- **Logging**: Implement logging to track the execution of commands and any errors that occur.

## Testing
Test your program with various command sequences and redirections to ensure it handles different scenarios correctly:
- **Basic Pipe**: Connect two simple commands.
- **Complex Pipe**: Connect multiple commands with complex piping.
- **Redirection**: Test input and output redirection with files.

Ensure the program behaves as expected in all cases, handling both valid and invalid inputs appropriately.
