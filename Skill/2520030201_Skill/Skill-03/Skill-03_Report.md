# Skill-03: Command History and Dynamic Memory

## 1. Objective

To implement command history using a linked list, support Up/Down arrow navigation using terminal escape sequences, dynamically resize the input buffer, prevent buffer overflow, and verify memory management using Valgrind.

## 2. Concepts Implemented

- Terminal escape sequences
- Command history
- Previous command navigation
- Next command navigation
- Input buffer management
- Dynamic memory allocation
- Dynamic buffer resizing using `realloc()`
- Linked list for command history
- Memory deallocation using `free()`
- Valgrind memory verification

## 3. Program Description

The program implements an interactive shell-like command interface.

The terminal is changed from normal canonical mode to raw input mode so that individual keyboard characters can be read immediately.

The program supports:

1. Enter key to submit a command.
2. Backspace to edit the current command.
3. Up arrow to recall previous commands.
4. Down arrow to move to newer commands.
5. Dynamic input-buffer expansion when the buffer becomes full.
6. `exit` command to terminate the program.
7. Dynamic command history stored using a linked list.

## 4. Command History

Each entered command is stored in a linked-list node.

Each node contains:

- The command string.
- A pointer to the next history node.

The functions used for history management are:

- `add_history()`
- `history_count()`
- `get_history_command()`
- `free_history()`

The Up and Down arrow keys are detected using terminal escape sequences.

For example, an arrow key begins with the Escape character followed by `[` and a control character.

## 5. Dynamic Input Buffer

The initial input-buffer size is:

```text
64 bytes
