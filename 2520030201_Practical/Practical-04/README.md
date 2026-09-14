# Practical 04 - Process Synchronization and Zombie Processes

## Objective

To understand process synchronization using `wait()` and `waitpid()`, and to study the creation and elimination of zombie processes.

## Task 1: Multiple Child Processes

### Program
`multiple_children.c`

The program creates two child processes.

- `waitpid()` is used to wait specifically for Child 2.
- `wait()` is then used to wait for the remaining child.
- The parent process completes only after both child processes finish.

### Difference Between wait() and waitpid()

| Function | Purpose |
|---|---|
| `wait()` | Waits for any child process to terminate |
| `waitpid()` | Waits for a specific child process |

### Sample Output

Parent Process PID: 1320  
Child 1 PID: 1321  
Child 2 PID: 1322  

Child 1 completed  
Child 2 completed  

Child 2 completed using waitpid()  
Remaining child completed using wait()  
Parent process completed

---

## Task 2: Zombie Process

### Program
`zombie_process.c`

A zombie process is a child process that has finished execution but whose exit status has not yet been collected by its parent.

In this program:

1. The child process terminates.
2. The parent does not immediately call `wait()`.
3. During this period, the child can appear as a zombie process with state `Z`.
4. The parent later calls `wait()`.
5. The zombie process is removed from the process table.

### Process Observation

The process can be checked using:

```bash
ps -o pid,ppid,state,stat,cmd -p PARENT_PID,CHILD_PID
