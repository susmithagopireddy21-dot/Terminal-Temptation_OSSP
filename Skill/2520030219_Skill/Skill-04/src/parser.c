#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

static void set_error(ParseResult *result, const char *message)
{
    result->valid = 0;
    snprintf(result->error, sizeof(result->error), "%s", message);
}

static int add_argument(Command *command, const char *value)
{
    char **temp = realloc(
        command->arguments,
        sizeof(char *) * (size_t)(command->argument_count + 2)
    );

    if (temp == NULL)
        return 0;

    command->arguments = temp;

    size_t length = strlen(value);
    command->arguments[command->argument_count] = malloc(length + 1);

    if (command->arguments[command->argument_count] == NULL)
        return 0;

    strcpy(command->arguments[command->argument_count], value);
    command->argument_count++;

    command->arguments[command->argument_count] = NULL;
    return 1;
}

static int add_command(ParseResult *result)
{
    Command *temp = realloc(
        result->commands,
        sizeof(Command) * (size_t)(result->command_count + 1)
    );

    if (temp == NULL)
        return 0;

    result->commands = temp;

    Command *command = &result->commands[result->command_count];
    memset(command, 0, sizeof(*command));

    result->command_count++;
    return 1;
}

static int is_redirect(TokenType type)
{
    return type == TOKEN_INPUT ||
           type == TOKEN_OUTPUT ||
           type == TOKEN_APPEND;
}

ParseResult parse_tokens(const TokenList *tokens)
{
    ParseResult result = {0};
    result.valid = 1;

    if (tokens == NULL || tokens->count < 0)
    {
        set_error(&result, "Invalid token list.");
        return result;
    }

    if (tokens->count == 0)
        return result;

    if (!add_command(&result))
    {
        set_error(&result, "Memory allocation failed.");
        return result;
    }

    for (int i = 0; i < tokens->count; i++)
    {
        Token token = tokens->tokens[i];
        Command *command = &result.commands[result.command_count - 1];

        if (token.type == TOKEN_WORD)
        {
            if (!add_argument(command, token.value))
            {
                set_error(&result, "Memory allocation failed.");
                break;
            }
        }
        else if (token.type == TOKEN_PIPE ||
                 token.type == TOKEN_SEMICOLON)
        {
command->separator_after = token.type;
            if (command->argument_count == 0)
            {
                set_error(&result,
                          "Missing command before separator.");
                break;
            }

            if (i == tokens->count - 1)
            {
                set_error(&result,
                          "Command cannot end with a separator.");
                break;
            }

            if (!add_command(&result))
            {
                set_error(&result, "Memory allocation failed.");
                break;
            }
        }
        else if (is_redirect(token.type))
        {
            if (i + 1 >= tokens->count ||
                tokens->tokens[i + 1].type != TOKEN_WORD)
            {
                set_error(&result,
                          "Redirection requires a filename.");
                break;
            }

            const char *filename = tokens->tokens[++i].value;
            char **target = NULL;

            if (token.type == TOKEN_INPUT)
                target = &command->input_file;
            else
                target = &command->output_file;

            char *copy = malloc(strlen(filename) + 1);

            if (copy == NULL)
            {
                set_error(&result, "Memory allocation failed.");
                break;
            }

            strcpy(copy, filename);
            free(*target);
            *target = copy;

            if (token.type == TOKEN_APPEND)
                command->append_output = 1;
            else if (token.type == TOKEN_OUTPUT)
                command->append_output = 0;
        }
        else
        {
            set_error(&result, "Unknown token type.");
            break;
        }
    }

    if (result.valid &&
        result.command_count > 0 &&
        result.commands[result.command_count - 1].argument_count == 0)
    {
        set_error(&result, "Empty command.");
    }

    if (!result.valid)
    {
        /* Keep the error message, but release partial parse data. */
        for (int i = 0; i < result.command_count; i++)
        {
            Command *command = &result.commands[i];

            for (int j = 0; j < command->argument_count; j++)
                free(command->arguments[j]);

            free(command->arguments);
            free(command->input_file);
            free(command->output_file);
        }

        free(result.commands);
        result.commands = NULL;
        result.command_count = 0;
    }

    return result;
}

void free_parse_result(ParseResult *result)
{
    if (result == NULL)
        return;

    for (int i = 0; i < result->command_count; i++)
    {
        Command *command = &result->commands[i];

        for (int j = 0; j < command->argument_count; j++)
            free(command->arguments[j]);

        free(command->arguments);
        free(command->input_file);
        free(command->output_file);
    }

    free(result->commands);
    result->commands = NULL;
    result->command_count = 0;
}

void print_parse_result(const ParseResult *result)
{
    if (!result->valid)
    {
        printf("Syntax error: %s\n", result->error);
        return;
    }

    if (result->command_count == 0)
    {
        printf("Empty command. Nothing to parse.\n");
        return;
    }

    printf("Parsed execution structure:\n");

    for (int i = 0; i < result->command_count; i++)
    {
        const Command *command = &result->commands[i];

        printf("Command %d:\n", i + 1);
        printf("  Arguments:");

        for (int j = 0; j < command->argument_count; j++)
            printf(" %s", command->arguments[j]);

        printf("\n");
if (command->separator_after == TOKEN_PIPE)
    printf("  Separator after: | (PIPE)\n");
else if (command->separator_after == TOKEN_SEMICOLON)
    printf("  Separator after: ; (SEMICOLON)\n");

        printf("  Input file: %s\n",
               command->input_file ? command->input_file : "(none)");

        printf("  Output file: %s\n",
               command->output_file ? command->output_file : "(none)");

        printf("  Append output: %s\n",
               command->append_output ? "yes" : "no");
    }
}
