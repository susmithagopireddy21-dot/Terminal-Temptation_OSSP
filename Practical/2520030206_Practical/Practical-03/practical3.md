# Practical 3 - Process Creation and State Transitions

## Objective

To develop a C program using fork() that creates a parent and child process and displays the Process ID (PID), Parent Process ID (PPID), and process states at different stages of execution.

To observe process state transitions such as Ready, Running, Waiting, and Terminated using Linux monitoring tools such as ps, top, and /proc.

## Program Description

The C program uses the fork() system call to create a child process.

The parent process displays its PID and waits for the child process using wait().

The child process displays its PID and PPID. It enters a sleeping state using sleep(), becomes active again, and finally terminates.

## Process State Transitions

### Parent Process

Running → Waiting for Child → Running Again → Terminated

### Child Process

Created → Running → Waiting/Sleeping → Running Again → Terminated

## Linux Monitoring Commands

### 1. ps

Command:

ps -o pid,ppid,state,stat,cmd -p <PID>

Observation:

The ps command displays the PID, PPID, process state, STAT value, and command.

The S state indicates that the child process is sleeping or waiting.

### 2. top

Command:

top -p <PID>

Observation:

The top command provides real-time information about the selected process.

The S value in the state column indicates that the child process is sleeping.

### 3. /proc

Command:

cat /proc/<PID>/status | grep -E "Name|State|Pid|PPid"

Observation:

The /proc filesystem provides information about a process, including its name, PID, PPID, and current state.

The State field showed:

S (sleeping)

## Observation Table

| Process State | Linux Observation |
|---|---|
| Ready / Runnable | R state indicates running or runnable |
| Running | Process is actively executing |
| Waiting / Sleeping | S state observed during sleep() |
| Terminated | Process disappears from the ps process list |

## Experiment Observation

The child process was created using fork().

The child process entered the sleeping state using sleep(). This state was observed using ps and top.

The /proc filesystem was used to obtain detailed information about the child process.

After the child process terminated, checking its PID using ps showed no process entry.

## Conclusion

The experiment demonstrates process creation using fork() and process synchronization using wait(). The PID and PPID of the parent and child processes were observed.

The process states were monitored using ps, top, and the /proc filesystem. The experiment demonstrated the transition of processes between running, waiting/sleeping, and terminated states.
