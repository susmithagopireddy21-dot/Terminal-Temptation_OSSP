
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "parser.h"

int main(void)
{
    char *input = NULL;
    size_t size = 0;

    printf("Skill-04 Tokenizer and Parser\n");
    printf("Enter a command (Ctrl+D to exit).\n");

    while (1)
    {
        printf("\nparser> ");
        fflush(stdout);

        ssize_t length = getline(&input, &size, stdin);

        if (length == -1)
            break;

        if (length > 0 && input[length - 1] == '\n')
            input[length - 1] = '\0';

        TokenList tokens = tokenize(input);

        if (tokens.count < 0)
        {
            printf("Tokenization error: invalid input or memory issue.\n");
            continue;
        }

        printf("\nTokens:\n");

        for (int i = 0; i < tokens.count; i++)
        {
            printf("  %-10s : %s\n",
                   token_type_name(tokens.tokens[i].type),
                   tokens.tokens[i].value);
        }

        ParseResult result = parse_tokens(&tokens);
        printf("\n");
        print_parse_result(&result);

        free_parse_result(&result);
        free_tokens(&tokens);
    }

    free(input);
    printf("\nExiting parser.\n");

    return 0;
}
