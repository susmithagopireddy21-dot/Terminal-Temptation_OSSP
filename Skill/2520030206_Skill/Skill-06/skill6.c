
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT 512
#define MAX_ARGS  32
#define MAX_ARG_LEN 128

int parse_command(const char *input, char *args[]) {
    static char storage[MAX_ARGS][MAX_ARG_LEN];
    int argc = 0;
    int in_token = 0;
    size_t j = 0;

    memset(storage, 0, sizeof(storage));

    for (size_t i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if (c == '\\') {
            if (input[i + 1] == '\0') {
                fprintf(stderr, "Parser error: trailing escape character.\n");
                return -1;
            }

            char next = input[++i];

            if (next == 'n')
                c = '\n';
            else if (next == 't')
                c = '\t';
            else
                c = next;

            if (!in_token) {
                if (argc >= MAX_ARGS - 1) {
                    fprintf(stderr, "Parser error: too many arguments.\n");
                    return -1;
                }
                in_token = 1;
                j = 0;
            }

            if (j >= MAX_ARG_LEN - 1) {
                fprintf(stderr, "Parser error: argument too long.\n");
                return -1;
            }

            storage[argc][j++] = c;
        } else if (isspace((unsigned char)c)) {
            if (in_token) {
                storage[argc][j] = '\0';
                args[argc] = storage[argc];
                argc++;
                in_token = 0;
                j = 0;
            }
        } else {
            if (!in_token) {
                if (argc >= MAX_ARGS - 1) {
                    fprintf(stderr, "Parser error: too many arguments.\n");
                    return -1;
                }
                in_token = 1;
                j = 0;
            }

            if (j >= MAX_ARG_LEN - 1) {
                fprintf(stderr, "Parser error: argument too long.\n");
                return -1;
            }

            storage[argc][j++] = c;
        }
    }

    if (in_token) {
        storage[argc][j] = '\0';
        args[argc] = storage[argc];
        argc++;
    }

    args[argc] = NULL;
    return argc;
}

int main(void) {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    printf("========================================\n");
    printf(" SKILL-06: ESCAPES AND CHILD PROCESSES\n");
    printf("========================================\n");
    printf("Examples: echo hello\\ world\n");
    printf("          echo line1\\nline2\n");
    printf("          ls -l\n");
    printf("Enter command: ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Input error.\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '\0') {
        fprintf(stderr, "Empty command.\n");
        return 1;
    }

    int argc = parse_command(input, args);
    if (argc <= 0) {
        fprintf(stderr, "Command parsing failed.\n");
        return 1;
    }

    printf("\nParsed arguments:\n");
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = [%s]\n", i, args[i]);
    }

    printf("\nCreating child process...\n");
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        execvp(args[0], args);
        fprintf(stderr, "Execution failed for '%s': %s\n",
                args[0], strerror(errno));
        _exit(127);
    }

    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid failed");
        return 1;
    }

    if (WIFEXITED(status)) {
        printf("\nChild process finished with exit code %d.\n",
               WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("\nChild process terminated by signal %d.\n",
               WTERMSIG(status));
    }

    return 0;
}
