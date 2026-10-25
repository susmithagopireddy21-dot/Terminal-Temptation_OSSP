#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

static int add_token(TokenList *list, TokenType type,
                     const char *start, size_t length)
{
    Token *temp = realloc(
        list->tokens,
        sizeof(Token) * (size_t)(list->count + 1)
    );

    if (temp == NULL)
        return 0;

    list->tokens = temp;

    char *value = malloc(length + 1);

    if (value == NULL)
        return 0;

    memcpy(value, start, length);
    value[length] = '\0';

    list->tokens[list->count].type = type;
    list->tokens[list->count].value = value;
    list->count++;

    return 1;
}

const char *token_type_name(TokenType type)
{
    switch (type)
    {
        case TOKEN_WORD: return "WORD";
        case TOKEN_PIPE: return "PIPE";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_INPUT: return "INPUT";
        case TOKEN_OUTPUT: return "OUTPUT";
        case TOKEN_APPEND: return "APPEND";
        default: return "UNKNOWN";
    }
}

TokenList tokenize(const char *input)
{
    TokenList list = {NULL, 0};
    size_t i = 0;

    while (input[i] != '\0')
    {
        if (isspace((unsigned char)input[i]))
        {
            i++;
            continue;
        }

        if (input[i] == '|')
        {
            if (!add_token(&list, TOKEN_PIPE, "|", 1))
                goto error;
            i++;
        }
        else if (input[i] == ';')
        {
            if (!add_token(&list, TOKEN_SEMICOLON, ";", 1))
                goto error;
            i++;
        }
        else if (input[i] == '<')
        {
            if (!add_token(&list, TOKEN_INPUT, "<", 1))
                goto error;
            i++;
        }
        else if (input[i] == '>')
        {
            if (input[i + 1] == '>')
            {
                if (!add_token(&list, TOKEN_APPEND, ">>", 2))
                    goto error;
                i += 2;
            }
            else
            {
                if (!add_token(&list, TOKEN_OUTPUT, ">", 1))
                    goto error;
                i++;
            }
        }
        else
        {
            char word[1024];
            size_t length = 0;
            char quote = '\0';

            while (input[i] != '\0')
            {
                char ch = input[i];

                if (quote == '\0' &&
                    (isspace((unsigned char)ch) ||
                     ch == '|' || ch == ';' ||
                     ch == '<' || ch == '>'))
                    break;

                if (ch == '\'' || ch == '"')
                {
                    if (quote == '\0')
                    {
                        quote = ch;
                        i++;
                        continue;
                    }
                    else if (quote == ch)
                    {
                        quote = '\0';
                        i++;
                        continue;
                    }
                }

                if (length + 1 >= sizeof(word))
                    goto error;

                word[length++] = ch;
                i++;
            }

            if (quote != '\0' || length == 0)
                goto error;

            if (!add_token(&list, TOKEN_WORD, word, length))
                goto error;
        }
    }

    return list;

error:
    free_tokens(&list);
    return (TokenList){NULL, -1};
}

void free_tokens(TokenList *list)
{
    if (list == NULL)
        return;

    for (int i = 0; i < list->count; i++)
        free(list->tokens[i].value);

    free(list->tokens);
    list->tokens = NULL;
    list->count = 0;
}
