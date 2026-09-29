# Skill-01 – Linux Environment, GCC and Makefile Setup

## Objective

To install and configure the Linux development environment, verify GCC, create a basic C project structure, understand the shell environment, configure a Git repository, and build and execute a C program using a Makefile.

---

## 1. Linux Environment

The project was developed using Ubuntu running through Windows Subsystem for Linux (WSL2).

The Linux system was verified using:

```bash
uname -a

## 2. GCC Verification

GCC was verified using:

gcc --version

The installed GCC version was:

gcc (Ubuntu 15.2.0-16ubuntu1) 15.2.0

GCC is used to compile C programs in the Linux environment.

---

## 3. Project Structure

The Skill project was organized inside the Git repository as follows:

```text
Terminal-Temptation_OSSP/
├── Practical/
└── Skill/
    ├── 2520030201_Skill/
    ├── 2520030206_Skill/
    │   └── Skill-01/
    │       ├── Makefile
    │       ├── main.c
    │       ├── README.md
    │       ├── Screenshot1.png
    │       ├── Screenshot2.png
    │       ├── Screenshot3.png
    │       └── Screenshot4.png
    └── 2520030219_Skill/
Shell Architecture

The shell environment was inspected using:

echo "$SHELL"
bash --version
ps -p $$ -o pid,ppid,comm,args

The shell was identified as:

/bin/bash

The Bash version was:

GNU bash, version 5.3.9(1)-release

The current shell process was also inspected to understand its process ID and parent process ID.
---

## 5. C Program

The file `main.c` contains a simple C program:

```c
#include <stdio.h>

int main() {
    printf("Skill-01: GCC setup and Makefile build successful.\n");
    return 0;
}

## 6. Makefile

The project uses a Makefile to automate compilation.

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = skill01
SOURCE = main.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm -f $(TARGET)
Makefile Components
CC specifies the GCC compiler.
CFLAGS enables warnings and uses the C11 standard.
TARGET specifies the executable name.
SOURCE specifies the C source file.
all builds the program.
clean removes the generated executable.
---

## 7. Build and Execution

The program was built using:

```bash
make clean
make
./skill01

## 8. Screenshots
Screenshot 1 – Makefile Build and Program Execution

This screenshot shows the make clean, make, and program execution commands.

![Makefile Build and Execution](Screenshot1.png)

Screenshot 2 – GCC and Linux System Verification

This screenshot shows the GCC version and Linux system information.

![GCC and Linux Verification](Screenshot2.png)

Screenshot 3 – Git Repository and Project Structure

This screenshot shows the Git remote repository and the Practical and Skill project structure.

![Git Repository and Project Structure](Screenshot3.png)

Screenshot 4 – Shell Architecture

This screenshot shows the Bash shell, Bash version, and current shell process information.

![Shell Architecture](Screenshot4.png)

## 9. Conclusion

The Linux development environment was successfully configured and verified. GCC was installed and working correctly, the Git repository and project structure were organized, the Bash shell environment was inspected, and a C program was successfully compiled and executed using a Makefile.
