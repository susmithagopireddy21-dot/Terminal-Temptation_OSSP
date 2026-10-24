
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 256
#define MAX_TOKEN 128
#define MAX_TOKENS 32

typedef enum {
    QUOTE_NONE,
    QUOTE_SINGLE,
    QUOTE_DOUBLE
} QuoteType;

typedef struct {
    char value[MAX_TOKEN];
    QuoteType quote_type;
} Token;

void expand_variables(char *value) {
    char result[MAX_TOKEN] = "";
    size_t i = 0;

    while (value[i] != '\0') {
        if (value[i] == '$') {
            i++;
            char name[64];
            size_t j = 0;

            while (isalnum((unsigned char)value[i]) ||
                   value[i] == '_') {
                if (j < sizeof(name) - 1)
                    name[j++] = value[i];
                i++;
            }

            name[j] = '\0';

            if (j == 0) {
                strncat(result, "$",
                        sizeof(result) - strlen(result) - 1);
            } else {
                const char *env_value = getenv(name);
                if (env_value != NULL)
                    strncat(result, env_value,
                            sizeof(result) - strlen(result) - 1);
            }
        } else {
            char part[2] = {value[i++], '\0'};
            strncat(result, part,
                    sizeof(result) - strlen(result) - 1);
        }
    }

    strcpy(value, result);
}

int tokenize(const char *input, Token tokens[]) {
    size_t i = 0;
    int count = 0;

    while (input[i] != '\0') {
        while (isspace((unsigned char)input[i]))
            i++;

        if (input[i] == '\0')
            break;

        if (count >= MAX_TOKENS) {
            printf("Error: Too many tokens.\n");
            return -1;
        }

        size_t j = 0;
        QuoteType quote = QUOTE_NONE;
        int saw_single = 0;
        int saw_double = 0;

        while (input[i] != '\0') {
            char c = input[i];

            if (quote == QUOTE_NONE &&
                isspace((unsigned char)c))
                break;

            if (quote == QUOTE_NONE && c == '\'') {
                quote = QUOTE_SINGLE;
                saw_single = 1;
                i++;
                continue;
            }

            if (quote == QUOTE_NONE && c == '"') {
                quote = QUOTE_DOUBLE;
                saw_double = 1;
                i++;
                continue;
            }

            if ((quote == QUOTE_SINGLE && c == '\'') ||
                (quote == QUOTE_DOUBLE && c == '"')) {
                quote = QUOTE_NONE;
                i++;
                continue;
            }

            if (j >= MAX_TOKEN - 1) {
                printf("Error: Token is too long.\n");
                return -1;
            }

            tokens[count].value[j++] = c;
            i++;
        }

        if (quote != QUOTE_NONE) {
            printf("Syntax error: Unclosed quote.\n");
            return -1;
        }

        tokens[count].value[j] = '\0';

        if (saw_single && !saw_double)
            tokens[count].quote_type = QUOTE_SINGLE;
        else if (saw_double && !saw_single)
            tokens[count].quote_type = QUOTE_DOUBLE;
        else if (saw_single || saw_double)
            tokens[count].quote_type = QUOTE_DOUBLE;
        else
            tokens[count].quote_type = QUOTE_NONE;

        count++;
    }

    return count;
}

int main(void) {
    char input[MAX_INPUT];
    Token tokens[MAX_TOKENS];

    printf("====================================\n");
    printf(" SKILL-05: QUOTED STRING PARSER\n");
    printf("====================================\n");
    printf("Example: echo 'Hello World' \"$HOME\"\n");
    printf("Enter input: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Input error.\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '\0') {
        printf("Empty input: nothing to parse.\n");
        return 0;
    }

    int count = tokenize(input, tokens);

    if (count < 0) {
        printf("Parsing failed.\n");
        return 1;
    }

    printf("\nParsed tokens:\n");

    for (int i = 0; i < count; i++) {
        if (tokens[i].quote_type == QUOTE_SINGLE) {
            printf("Token %d: '%s' (single-quoted; literal)\n",
                   i + 1, tokens[i].value);
        } else if (tokens[i].quote_type == QUOTE_DOUBLE) {
            expand_variables(tokens[i].value);
            printf("Token %d: \"%s\" (double-quoted; expanded)\n",
                   i + 1, tokens[i].value);
        } else {
            expand_variables(tokens[i].value);
            printf("Token %d: %s (unquoted; expanded)\n",
                   i + 1, tokens[i].value);
        }
    }

    printf("\nParsing validation: SUCCESS\n");
    printf("Total tokens: %d\n", count);

    return 0;
}
