#ifndef PARSER_C
#define PARSER_C

#include "../nodes/node_structs.h"
#include "../nodes/nodes.h"
#include "../lexer/lexer.h"

#include "utils.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define f parse_token_stmt
/**
 * @brief Parses a primary expression.
 *
 * @param token The token.
 * @return Stmt*
 */
Stmt *parse_token_stmt(Token *token)
{
    // Check the token type
    switch (token->type)
    {
    // These return a NODE_TYPE_REGULAR_EXPRESSION Statement
    // This is used for determining (so far) how to print the stmt
    case TOKEN_TYPE_IDENTIFIER:
        // The provided type gets set to the stmt->expr->type
        // This will be used when walking the AST
        return new_expr_stmt(NODE_TYPE_IDENTIFIER, token->value);
    case TOKEN_TYPE_NUMBER:
        return new_expr_stmt(NODE_TYPE_NUMERIC_LITERAL, token->value);
    
    // These return a NODE_TYPE_BINARY_EXPRESSION Statement
    case TOKEN_TYPE_PLUS:
    case TOKEN_TYPE_MINUS:
    case TOKEN_TYPE_MULTIPLY:
    case TOKEN_TYPE_DIVIDE:
        return new_bin_expr_stmt(NULL, NULL, token->value);
    default:
        return NULL;
    }
}
#undef f

#define f parse_multiplicative_stmt
/**
 * @brief Parses a multiplicative expression.
 *
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 * @param index The current index.
 * @return Stmt*
 */
Stmt *parse_multiplicative_stmt(Token **tokens, int *index)
{
    // Get the first token
    Stmt *res = parse_token_stmt(tokens[*index]);

    // While (true)
    for (;;)
    {
        // Increment the index to get the middle token
        (*index)++;

        // Get the current token
        Token *op = tokens[*index];
        if (op->type != TOKEN_TYPE_MULTIPLY && op->type != TOKEN_TYPE_DIVIDE)
            break;

        // Increment the index to get the next token
        (*index)++;

        // Parse the next token
        Stmt *right = parse_token_stmt(tokens[*index]);

        // Set to a binary expression
        if (res->type == NODE_TYPE_REGULAR_EXPRESSION)
            set_stmt_to_binary_expr(res, new_bin_expr_stmt(NULL, res->expr, NULL)->bin_expr);

        // Update the binary expression
        res->bin_expr = new_bin_expr_stmt(res->bin_expr, right->expr, op->value)->bin_expr;
    }

    // Return the result statement
    return res;
}
#undef f

#define f parse_additive_stmt
/**
 * @brief Parses an additive expression.
 *
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 * @param index The current index.
 * @return Stmt*
 */
Stmt *parse_additive_stmt(Token **tokens, int *index)
{
    // Get the first token
    Stmt *res = parse_multiplicative_stmt(tokens, index);

    // While (true)
    for (;;)
    {
        // Get the current token
        Token *op = tokens[*index];
        if (op->type != TOKEN_TYPE_PLUS && op->type != TOKEN_TYPE_MINUS)
            break;

        // Increment the index to get the next token
        (*index)++;

        // Parse the next token
        Stmt *right = parse_token_stmt(tokens[*index]);

        // Set to a binary expression
        if (res->type == NODE_TYPE_REGULAR_EXPRESSION)
            set_stmt_to_binary_expr(res, new_bin_expr_stmt(NULL, res->expr, NULL)->bin_expr);

        // Update the binary expression
        res->bin_expr = new_bin_expr_stmt(res->bin_expr, right->expr, op->value)->bin_expr;

        // Increment the index to go back to the middle token
        (*index)++;
    }

    // Free opposite expressions (Unnecessary with set_stmt_to_binary_expr)
    // free_stmt_unused_mem(res);

    // Return the result statement
    return res;
}
#undef f

#define f parse_stmt
/**
 * @brief Parses a statement
 *
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 * @param index The current index.
 * @return Stmt*
 */
Stmt *parse_stmt(Token **tokens, int *index)
{
    return parse_additive_stmt(tokens, index);
}
#undef f

#define f push_back_stmt
/**
 * @brief Pushes back a statement to the program body.
 *
 * @param program The program.
 * @param stmt The statement.
 * @return void
 */
void push_back_stmt(Program *program, Stmt *stmt)
{
    // Create a tmp array
    Stmt **tmp = malloc(sizeof(Stmt) * (program->body_size + 1));

    // Copy the body to the tmp array
    memcpy(tmp, program->body, sizeof(Stmt) * program->body_size);

    // Free the body
    free(program->body);

    // Set the body to the tmp array
    program->body = tmp;

    // Set the body at the current index to the statement
    program->body[program->body_size] = stmt;

    // Increment the body size
    program->body_size++;
}
#undef f

#define f parse_program
/**
 * @brief Parses a program.
 *
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 * @return Program*
 */
Program *parse_program(Token **tokens, size_t tokens_size)
{
    // Initialize the program
    Program *program = malloc(sizeof(Program));
    program->type = NODE_TYPE_PROGRAM;
    program->body = malloc(sizeof(Stmt) * tokens_size);
    program->body_size = 0;

    // While not EOF
    int index = 0;
    for (; index < tokens_size;)
    {
        // Parse the statement
        Stmt *stmt = parse_stmt(tokens, &index);

        // Pushback the statement to the body
        push_back_stmt(program, stmt);

        // Increment the index
        index++;
    }

    printf("Parsed %d statements\n", (int)program->body_size);

    // Return the program
    return program;
}
#undef f

/**
 * @brief Parses tokens.
 *
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 */
void parser(Token **tokens, size_t tokens_size)
{
    Program *program = parse_program(tokens, tokens_size);
    print_program(program);
}

#endif // PARSER_C