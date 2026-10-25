#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"

typedef struct
{
    char **arguments;
    int argument_count;

    char *input_file;
    char *output_file;
    int append_output;
    TokenType separator_after;
} Command;

typedef struct
{
    Command *commands;
    int command_count;
    int valid;
    char error[128];
} ParseResult;

ParseResult parse_tokens(const TokenList *tokens);
void free_parse_result(ParseResult *result);
void print_parse_result(const ParseResult *result);

#endif
