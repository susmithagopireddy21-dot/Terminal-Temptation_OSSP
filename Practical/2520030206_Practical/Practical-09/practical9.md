# Practical 9 - Linux File I/O and I/O Redirection

## Aim

To implement a file copy utility using low-level Linux file I/O system calls such as `open()`, `read()`, `write()`, `lseek()`, and `close()`, compare its performance with standard library functions such as `fopen()`, `fread()`, and `fwrite()`, and demonstrate standard input/output redirection using `dup2()`.

## 1. Low-Level File Copy

The program `low_level_copy.c` uses the following Linux system calls:

- `open()` - opens the source and destination files.
- `read()` - reads data from the source file.
- `write()` - writes data to the destination file.
- `lseek()` - checks the current file position.
- `close()` - closes the file descriptors.

### Output

The 66-byte source file was successfully copied.

The source file position after copying was:

```text
66 bytes

2. Standard Library File Copy

The program stdio_copy.c uses:

fopen() - opens files.
fread() - reads data.
fwrite() - writes data.
fclose() - closes files.

A 10 MiB file was used to compare the performance of both methods.

Performance Comparison
Method	Functions Used	Execution Time
Low-level I/O	open(), read(), write()	0.01 seconds
Standard library	fopen(), fread(), fwrite()	0.01 seconds

Both methods produced identical output files, verified using the cmp command.

3. Standard Input and Output Redirection Using dup2()

The program io_redirection.c demonstrates how file descriptors can be redirected using dup2().

The program:

Opens an input file.
Opens an output file.
Uses dup2() to redirect standard input (STDIN_FILENO).
Uses dup2() to redirect standard output (STDOUT_FILENO).
Reads data using standard input.
Writes the result using standard output.

The redirected output was successfully stored in output.txt.

4. Relation to Shell I/O Redirection

Linux shells implement commands such as:

command < input.txt > output.txt

by opening the required files and redirecting the standard file descriptors before executing the command.

The dup2() system call provides the mechanism for replacing the standard input and output file descriptors with file descriptors referring to files.

5. Observation
Low-level system calls provide direct control over file descriptors.
Standard library functions provide a higher-level interface for file operations.
Both methods successfully copied the test file.
For the 10 MiB test file, both methods took approximately 0.01 seconds in the measured run.
dup2() successfully redirected standard input and standard output.
Conclusion

The file copy utility was successfully implemented using low-level Linux file I/O system calls and compared with standard library file operations. Standard input and output redirection was also successfully demonstrated using dup2(), showing the basic mechanism used by shells for I/O redirection.
