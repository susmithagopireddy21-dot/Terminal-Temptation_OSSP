#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 256
#define MAX_TOKENS 32
#define MAX_TOKEN_LEN 64

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_IN,
    TOKEN_SEMICOLON
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LEN];
} Token;

typedef struct {
    char command[MAX_TOKEN_LEN];
    char *arguments[MAX_TOKENS];
    int argument_count;
} CommandNode;

const char *token_type_name(TokenType type) {
    switch (type) {
        case TOKEN_WORD: return "WORD";
        case TOKEN_PIPE: return "PIPE";
        case TOKEN_REDIRECT_OUT: return "REDIRECT_OUT";
        case TOKEN_REDIRECT_IN: return "REDIRECT_IN";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        default: return "UNKNOWN";
    }
}

int tokenize(const char *input, Token tokens[]) {
    int count = 0;
    int i = 0;

    while (input[i] != '\0') {
        if (isspace((unsigned char)input[i])) {
            i++;
            continue;
        }

        if (count >= MAX_TOKENS) {
            printf("Error: Too many tokens.\n");
            return -1;
        }

        TokenType type;

        switch (input[i]) {
            case '|': type = TOKEN_PIPE; break;
            case '>': type = TOKEN_REDIRECT_OUT; break;
            case '<': type = TOKEN_REDIRECT_IN; break;
            case ';': type = TOKEN_SEMICOLON; break;
            default: type = TOKEN_WORD;
        }

        tokens[count].type = type;
        int j = 0;

        if (type != TOKEN_WORD) {
            tokens[count].value[j++] = input[i++];
        } else {
            while (input[i] != '\0' &&
                   !isspace((unsigned char)input[i]) &&
                   input[i] != '|' && input[i] != '>' &&
                   input[i] != '<' && input[i] != ';') {
                if (j >= MAX_TOKEN_LEN - 1) {
                    printf("Error: Token is too long.\n");
                    return -1;
                }
                tokens[count].value[j++] = input[i++];
            }
        }

        tokens[count].value[j] = '\0';
        count++;
    }

    return count;
}

int parse_tokens(Token tokens[], int count) {
    int expect_command = 1;
    int expect_filename = 0;
    int command_count = 0;

    printf("\nParser output:\n");

    for (int i = 0; i < count; i++) {
        if (tokens[i].type == TOKEN_WORD) {
            if (expect_filename) {
                printf("  Redirection target: %s\n", tokens[i].value);
                expect_filename = 0;
                expect_command = 0;
            } else if (expect_command) {
                printf("  Command: %s\n", tokens[i].value);
                command_count++;
                expect_command = 0;
            } else {
                printf("  Argument: %s\n", tokens[i].value);
            }
        } else if (tokens[i].type == TOKEN_PIPE) {
            if (expect_command || expect_filename) {
                printf("Syntax error: Unexpected pipe '|'.\n");
                return 0;
            }
            printf("  Parse tree: PIPE node\n");
            expect_command = 1;
        } else if (tokens[i].type == TOKEN_REDIRECT_OUT ||
                   tokens[i].type == TOKEN_REDIRECT_IN) {
            if (expect_filename) {
                printf("Syntax error: Missing redirection target.\n");
                return 0;
            }
            if (expect_command) {
                printf("Syntax error: Redirection without a command.\n");
                return 0;
            }
            printf("  Parse tree: %s node\n",
                   tokens[i].type == TOKEN_REDIRECT_OUT
                   ? "OUTPUT_REDIRECTION" : "INPUT_REDIRECTION");
            expect_filename = 1;
        } else if (tokens[i].type == TOKEN_SEMICOLON) {
            if (expect_command || expect_filename) {
                printf("Syntax error: Empty command or missing target.\n");
                return 0;
            }
            printf("  Parse tree: SEQUENCE node\n");
            expect_command = 1;
        }
    }

    if (expect_filename) {
        printf("Syntax error: Missing redirection target.\n");
        return 0;
    }

    if (expect_command && count > 0) {
        printf("Syntax error: Command cannot end with a separator.\n");
        return 0;
    }

    if (command_count == 0) {
        printf("No executable command found.\n");
        return 0;
    }

    printf("Syntax validation: SUCCESS\n");
    printf("Execution structure: %d command(s) recognized.\n",
           command_count);
    return 1;
}

int main(void) {
    char input[MAX_INPUT];
    Token tokens[MAX_TOKENS];

    printf("====================================\n");
    printf("   SKILL-04: TOKENIZER AND PARSER\n");
    printf("====================================\n");
    printf("Supported delimiters: |  >  <  ;\n");
    printf("Enter a command (or type exit):\n> ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Input error.\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "exit") == 0) {
        printf("Exiting parser.\n");
        return 0;
    }

    if (input[0] == '\0' ||
        strspn(input, " \t\r\n") == strlen(input)) {
        printf("Empty command: nothing to parse.\n");
        return 0;
    }

    int count = tokenize(input, tokens);

    if (count < 0) {
        printf("Tokenization failed.\n");
        return 1;
    }

    printf("\nToken stream:\n");
    for (int i = 0; i < count; i++) {
        printf("  [%d] %-15s : %s\n",
               i + 1, token_type_name(tokens[i].type),
               tokens[i].value);
    }

    if (count == 0) {
        printf("Empty token stream.\n");
        return 0;
    }

    parse_tokens(tokens, count);
    return 0;
}
