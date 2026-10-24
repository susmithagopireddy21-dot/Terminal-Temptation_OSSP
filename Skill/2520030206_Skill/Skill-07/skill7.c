#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_PATH_LEN 4096
#define MAX_COMMAND_LEN 256

int find_executable(const char *command, char *result, size_t result_size) {
    if (command == NULL || command[0] == '\0')
        return 0;

    /* If the command includes a slash, check that exact path. */
    if (strchr(command, '/') != NULL) {
        struct stat info;

        if (stat(command, &info) == 0 &&
            S_ISREG(info.st_mode) &&
            access(command, X_OK) == 0) {
            if (realpath(command, result) == NULL) {
                if (snprintf(result, result_size, "%s", command)
                    >= (int)result_size)
                    return 0;
            }
            return 1;
        }
        return 0;
    }

    const char *path_env = getenv("PATH");
    if (path_env == NULL) {
        fprintf(stderr, "PATH environment variable is not set.\n");
        return 0;
    }

    char *path_copy = strdup(path_env);
    if (path_copy == NULL) {
        perror("strdup");
        return 0;
    }

    char *saveptr = NULL;
    char *directory = strtok_r(path_copy, ":", &saveptr);

    while (directory != NULL) {
        /* An empty PATH component represents the current directory. */
        const char *dir = directory[0] == '\0' ? "." : directory;
        char candidate[MAX_PATH_LEN];
        int n = snprintf(candidate, sizeof(candidate), "%s/%s",
                         dir, command);

        if (n >= 0 && (size_t)n < sizeof(candidate)) {
            struct stat info;

            if (stat(candidate, &info) == 0 &&
                S_ISREG(info.st_mode) &&
                access(candidate, X_OK) == 0) {
                if (snprintf(result, result_size, "%s", candidate)
                    >= (int)result_size) {
                    free(path_copy);
                    return 0;
                }

                free(path_copy);
                return 1;
            }
        }

        directory = strtok_r(NULL, ":", &saveptr);
    }

    free(path_copy);
    return 0;
}

int main(void) {
    char command[MAX_COMMAND_LEN];
    char executable[MAX_PATH_LEN];

    printf("========================================\n");
    printf(" SKILL-07: PATH SEARCH AND WAITPID\n");
    printf("========================================\n");

    const char *path = getenv("PATH");
    printf("\nPATH environment variable:\n%s\n",
           path != NULL ? path : "(not set)");

    printf("\nEnter a command to locate and execute (e.g., ls): ");
    fflush(stdout);

    if (fgets(command, sizeof(command), stdin) == NULL) {
        fprintf(stderr, "Input error.\n");
        return 1;
    }

    command[strcspn(command, "\n")] = '\0';

    if (command[0] == '\0') {
        fprintf(stderr, "Empty command.\n");
        return 1;
    }

    printf("\nSearching for executable...\n");

    if (!find_executable(command, executable, sizeof(executable))) {
        printf("Command '%s' was not found as an executable.\n", command);
        printf("Command resolution: FAILED\n");
        return 127;
    }

    printf("Executable found: %s\n", executable);
    printf("Executable permission: verified\n");
    printf("Command resolution: SUCCESS\n");

    printf("\nCreating child process...\n");
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        char *const args[] = {command, NULL};
        execv(executable, args);

        fprintf(stderr, "Execution failed: %s\n", strerror(errno));
        _exit(127);
    }

    int status;
    pid_t waited = waitpid(pid, &status, 0);

    if (waited < 0) {
        perror("waitpid");
        return 1;
    }

    printf("\nParent process: child PID %ld has finished.\n", (long)waited);

    if (WIFEXITED(status)) {
        printf("Child exited normally with status %d.\n",
               WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Child terminated by signal %d.\n", WTERMSIG(status));
    }

    return 0;
}
