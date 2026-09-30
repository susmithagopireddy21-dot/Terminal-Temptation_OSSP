# Skill-02: Interactive Input Loop and Keyboard Input Handling

## Objective

To create an interactive input loop that displays a prompt, reads user
input, handles exit conditions, and manages the control flow.

The second part is to capture keyboard input, handle the Backspace key,
process the Enter key, manage an input buffer, support multi-character
commands, and test user interaction.

## Tools Used

- Linux / Ubuntu WSL
- GCC
- GNU Make
- C
- POSIX terminal functions

## Program

The program `skill02_shell.c` implements a simple interactive shell-like
input loop.

It performs the following tasks:

1. Displays the `Skill-02>` prompt.
2. Captures keyboard input one character at a time.
3. Stores characters in an input buffer.
4. Supports multi-character input.
5. Handles the Enter key.
6. Handles the Backspace key.
7. Checks for the `exit` command.
8. Repeats the input loop until `exit` is entered.

## Main Loop

The main loop continuously displays the prompt and waits for user input.

The basic control flow is:

```text
Start
  |
  v
Allocate Input Buffer
  |
  v
Configure Terminal
  |
  v
Display Prompt
  |
  v
Read One Character
  |
  +---------> Backspace?
  |              |
  |             Yes
  |              |
  |       Remove Last Character
  |              |
  |              v
  |         Read Next Character
  |
  +---------> Enter?
  |              |
  |             Yes
  |              |
  |       Finish Input String
  |              |
  |              v
  |        Check for "exit"
  |           /       \
  |         Yes        No
  |          |          |
  |        Exit       Display
  |                   Input
  |                      |
  |                      v
  |                Display Prompt
  |
  +---------> Normal Character
                 |
                 v
          Store in Buffer
                 |
                 v
           Read Next Character# Skill-02: Interactive Input Loop and Keyboard Input Handling

## Objective

To create an interactive input loop that displays a prompt, reads user
input, handles exit conditions, and manages the control flow.

The second part is to capture keyboard input, handle the Backspace key,
process the Enter key, manage an input buffer, support multi-character
commands, and test user interaction.

## Tools Used

- Linux / Ubuntu WSL
- GCC
- GNU Make
- C
- POSIX terminal functions

## Program

The program `skill02_shell.c` implements a simple interactive shell-like
input loop.

It performs the following tasks:

1. Displays the `Skill-02>` prompt.
2. Captures keyboard input one character at a time.
3. Stores characters in an input buffer.
4. Supports multi-character input.
5. Handles the Enter key.
6. Handles the Backspace key.
7. Checks for the `exit` command.
8. Repeats the input loop until `exit` is entered.

## Main Loop

The main loop continuously displays the prompt and waits for user input.

The basic control flow is:

```text
Start
  |
  v
Allocate Input Buffer
  |
  v
Configure Terminal
  |
  v
Display Prompt
  |
  v
Read One Character
  |
  +---------> Backspace?
  |              |
  |             Yes
  |              |
  |       Remove Last Character
  |              |
  |              v
  |         Read Next Character
  |
  +---------> Enter?
  |              |
  |             Yes
  |              |
  |       Finish Input String
  |              |
  |              v
  |        Check for "exit"
  |           /       \
  |         Yes        No
  |          |          |
  |        Exit       Display
  |                   Input
  |                      |
  |                      v
  |                Display Prompt
  |
  +---------> Normal Character
                 |
                 v
          Store in Buffer
                 |
                 v
           Read Next Character
