# Practical-06 – Named Pipes (FIFOs) and POSIX Signal Handling

## Objective

To create a client-server application using Named Pipes (FIFOs), where the client sends messages and the server processes and responds to them.

To analyze FIFO behavior when multiple clients communicate with the server.

To create a POSIX signal handling program that captures `SIGINT`, `SIGTERM`, and `SIGUSR1`, demonstrate asynchronous event handling, and explain the role of signal handlers.

## 1. Client-Server Communication Using Named Pipe

### Server Program

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    char message[100];
    int fd;

    mkfifo("server_fifo", 0666);

    printf("Server started. Waiting for clients...\n");

    while (1)
    {
        fd = open("server_fifo", O_RDONLY);

        if (read(fd, message, sizeof(message)) > 0)
        {
            printf("Client message: %s", message);
        }

        close(fd);

        fd = open("server_fifo", O_WRONLY);

        write(fd, "Message processed by server", 28);

        close(fd);

        printf("Response sent to client\n\n");
    }

    return 0;
}
```

### Client Program

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char message[100];
    char response[100];

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    fd = open("server_fifo", O_WRONLY);

    write(fd, message, strlen(message) + 1);

    close(fd);

    fd = open("server_fifo", O_RDONLY);

    read(fd, response, sizeof(response));

    printf("Server response: %s\n", response);

    close(fd);

    return 0;
}
```

### Compilation

```bash
gcc server.c -o server
gcc client.c -o client
```

### Initial Client-Server Execution

Client output:

```text
Enter message: Hello Server
Server response: Message processed by server
```

Server output:

```text
Server started. Waiting for clients...
Client message: Hello Server
Response sent to client
```

The client successfully sent a message through the named pipe and received a response from the server.

## 2. Multiple Client Communication

The server was modified to continuously wait for clients using a `while(1)` loop.

Multiple client messages were successfully processed.

### Server Output

```text
Server started. Waiting for clients...
Client message: Client 2
Response sent to client

Client message: Client 3
Response sent to client

Client message: Client 4
Response sent to client

Client message: Client 5
Response sent to client
```

### Client Output

```text
Enter message: Client 4
Server response: Message processed by server

Enter message: Client 5
Server response: Message processed by server
```

### FIFO Behavior Analysis

A named pipe (FIFO) provides a communication channel between processes using a file-system name.

The server creates the FIFO using `mkfifo()` and waits for messages from clients.

When multiple clients communicate with the server, their messages are received as they become available. The server processes each message and sends a response.

This experiment demonstrates that a FIFO can be used for communication between independent processes. A server can continuously process client requests by repeatedly opening and reading from the FIFO.

## 3. POSIX Signal Handling

### Signal Program

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("\nSIGINT received\n");
    }
    else if (sig == SIGTERM)
    {
        printf("\nSIGTERM received\n");
    }
    else if (sig == SIGUSR1)
    {
        printf("\nSIGUSR1 received\n");
    }
}

int main()
{
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGUSR1, signal_handler);

    printf("Signal handling program started\n");
    printf("PID: %d\n", getpid());
    printf("Waiting for signals...\n");

    while (1)
    {
        pause();
    }

    return 0;
}
```

### Compilation

```bash
gcc signal.c -o signal
```

### Execution

The program was executed and produced:

```text
Signal handling program started
PID: 3906
Waiting for signals...
```

The process ID was `3906`.

### Testing SIGUSR1

Command:

```bash
kill -SIGUSR1 3906
```

Output:

```text
SIGUSR1 received
```

### Testing SIGINT

`Ctrl+C` was pressed in the terminal.

Output:

```text
SIGINT received
```

The program continued running because the signal handler handled `SIGINT`.

### Testing SIGTERM

Command:

```bash
kill -SIGTERM 3906
```

Output:

```text
SIGTERM received
```

The program continued running because `SIGTERM` was handled by the signal handler.

### Terminating the Process

The process was finally terminated using:

```bash
kill -9 3906
```

Output:

```text
Killed                     ./signal
```

The command:

```bash
ps -p 3906
```

showed no active process, confirming that the process was terminated.

## 4. Role of Signal Handlers

A signal handler is a function that is executed when a particular signal is received by a process.

Signal handlers allow a program to respond to asynchronous events without continuously checking for them.

In this program:

| Signal | Purpose |
|---|---|
| `SIGINT` | Interrupt signal, commonly generated using `Ctrl+C`. |
| `SIGTERM` | Requests a process to terminate. |
| `SIGUSR1` | User-defined signal used for application-specific events. |

The `signal()` function associates each signal with the `signal_handler()` function.

The `pause()` function allows the process to wait for incoming signals.

## 5. System Calls and Functions Used

| Function | Purpose |
|---|---|
| `mkfifo()` | Creates a named pipe. |
| `open()` | Opens the FIFO for reading or writing. |
| `read()` | Reads data from the FIFO. |
| `write()` | Writes data to the FIFO. |
| `close()` | Closes the FIFO file descriptor. |
| `signal()` | Registers a signal handler. |
| `pause()` | Waits for a signal. |
| `getpid()` | Gets the process ID. |
| `kill()` | Sends a signal to a process. |

## 6. Result

The client-server application using a named pipe was successfully implemented.

The client successfully sent messages to the server and received responses.

Multiple client messages were successfully processed by the server using the FIFO.

The POSIX signal handling program successfully captured and handled `SIGINT`, `SIGTERM`, and `SIGUSR1`.

## 7. Conclusion

This practical demonstrated Inter-Process Communication using Named Pipes (FIFOs) and asynchronous event handling using POSIX signals.

The FIFO experiment showed how independent processes can communicate through a named communication channel. Multiple client messages were successfully received and processed by the server.

The signal handling experiment demonstrated how a process can respond to asynchronous events using signal handlers. `SIGINT`, `SIGTERM`, and `SIGUSR1` were successfully captured and handled.

Thus, FIFOs provide a useful mechanism for process communication, while POSIX signals allow processes to respond to events asynchronously.
