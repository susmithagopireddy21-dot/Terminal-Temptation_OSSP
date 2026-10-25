#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_SEMICOLON,
    TOKEN_INPUT,
    TOKEN_OUTPUT,
    TOKEN_APPEND
} TokenType;

typedef struct
{
    TokenType type;
    char *value;
} Token;

typedef struct
{
    Token *tokens;
    int count;
} TokenList;

TokenList tokenize(const char *input);
void free_tokens(TokenList *list);
const char *token_type_name(TokenType type);

#endif
