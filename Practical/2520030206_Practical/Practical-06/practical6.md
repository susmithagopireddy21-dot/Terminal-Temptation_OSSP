# Practical 6 - FIFO Client-Server Communication and POSIX Signal Handling

## Objective

1. To create a client-server application using Named Pipes (FIFOs), where the client sends messages and the server processes and responds to them.
2. To observe FIFO behavior when multiple clients communicate with the server.
3. To create a POSIX signal handling program that captures SIGINT, SIGTERM, and SIGUSR1.
4. To demonstrate asynchronous event handling using signal handlers.

---

# Part A - Client-Server Communication Using Named Pipes

## Introduction

A Named Pipe or FIFO (First In First Out) is a special file used for communication between processes.

Unlike an ordinary pipe, a FIFO has a name in the filesystem and can be accessed by unrelated processes.

In this experiment, two FIFOs are used:

- `client_to_server` - used by the client to send messages to the server.
- `server_to_client` - used by the server to send responses back to the client.

## Server Program

The server creates the required FIFOs using `mkfifo()`.

It continuously waits for messages from clients. After receiving a message, it processes the message and sends a response back through the server-to-client FIFO.

The server continues running and can handle multiple clients one after another.

## Client Program

The client accepts a message from the user and writes it to the `client_to_server` FIFO.

It then reads the server's response from the `server_to_client` FIFO and displays the response.

## FIFO Communication Flow

Client

↓

`client_to_server`

↓

Server

↓

`server_to_client`

↓

Client

## Multiple Client Communication

The server was tested with two clients.

The first client sent:

`Client 1 Message`

The server processed the message and sent a response.

The second client then sent:

`Client 2 Message`

The server processed the second message and sent another response.

The server handles these requests sequentially.

This demonstrates that a FIFO can be used for communication between multiple client processes. True simultaneous parallel processing would require additional mechanisms such as separate processes or threads for handling clients.

## Observation

The client successfully sent messages to the server through the named FIFO.

The server received and processed the messages and returned responses through the second FIFO.

The server remained active and accepted another client request after completing the previous request.

---

# Part B - POSIX Signal Handling

## Introduction

Signals are asynchronous notifications sent to a process to indicate that an event has occurred.

The program registers signal handlers for:

- SIGINT
- SIGTERM
- SIGUSR1

The `signal()` function is used to register the handlers.

The `pause()` function keeps the process waiting until a signal is received.

## Signal Handler

The signal handler checks which signal was received and displays a corresponding message.

The signals were tested using the following commands:

```bash
kill -SIGINT <PID>
kill -SIGUSR1 <PID>
kill -SIGTERM <PID>
