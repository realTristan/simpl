#ifndef PARSER_C
#define PARSER_C

#include "../nodes/nodes.h"
#include "../lexer/lexer.h"

#include "utils.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define f is_eof
/**
 * @brief Checks if the token at the given index is an EOF token.
 *
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 * @param index The current index.
 * @return true
 * @return false
 */
bool is_eof(Token **tokens, size_t tokens_size, int index)
{
    return tokens[index]->type == TOKEN_TYPE_EOF;
}
#undef f

#define f new_expr
/**
 * @brief Creates a new expression.
 *
 * @param type The type of the expression.
 * @param token The token.
 * @return Expr*
 */
Expr *new_expr(NodeType type, Token *token)
{
    Expr *expr = (Expr *)malloc(sizeof(Expr));
    expr->type = type;
    expr->value = token->value;
    return expr;
}
#undef f

#define f parse_primary_expr
/**
 * @brief Parses a primary expression.
 *
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 * @param index The current index.
 * @return Expr*
 */
Expr *parse_primary_expr(Token **tokens, size_t tokens_size, int *index)
{
    Token *token = tokens[*index];
    switch (token->type)
    {
    case TOKEN_TYPE_IDENTIFIER:
        return new_expr(NODE_TYPE_IDENTIFIER, token);
    case TOKEN_TYPE_NUMBER:
        return new_expr(NODE_TYPE_NUMERIC_LITERAL, token);
    case TOKEN_TYPE_PLUS:
    case TOKEN_TYPE_MINUS:
    case TOKEN_TYPE_MULTIPLY:
    case TOKEN_TYPE_DIVIDE:
        return new_expr(NODE_TYPE_BINARY_EXPRESSION, token);
    default:
        printf("Unexpected token: %s\n", token->value);
        exit(1);
    }
    return NULL;
}
#undef f

#define f new_binary_expr
/**
 * @brief Creates a new binary expression.
 *
 * @param left The left expression.
 * @param right The right expression.
 * @param op The operator.
 * @return Expr*
 */
Expr *new_binary_expr(Expr *left, Expr *right, char *op)
{
    Expr *expr = (Expr *)malloc(sizeof(Expr));
    expr->type = NODE_TYPE_BINARY_EXPRESSION;
    expr->left = left;
    expr->right = right;
    expr->op = op;
    return expr;
}
#undef f

#define f parse_multiplicative_expr
/**
 * @brief Parses a multiplicative expression.
 *
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 * @param index The current index.
 * @return Expr*
 */
Expr *parse_multiplicative_expr(Token **tokens, size_t tokens_size, int *index)
{
    // Create a tmp index
    int tmp_index = *index;

    // Parse the left expression
    Expr *left = parse_primary_expr(tokens, tokens_size, &tmp_index);

    // Increment the index
    tmp_index++;

    // Get the current token
    Token *token = tokens[tmp_index];

    // While the current token is a star or slash token
    while (token->type == TOKEN_TYPE_MULTIPLY || token->type == TOKEN_TYPE_DIVIDE)
    {
        // Increment the index
        tmp_index++;

        // Parse the right expression
        Expr *right = parse_primary_expr(tokens, tokens_size, &tmp_index);

        // Create a new binary expression
        left = new_binary_expr(left, right, token->value);

        // Get the current token
        token = tokens[tmp_index];
    }

    // Set the index to the tmp index
    *index = tmp_index;

    // Return the left expression
    return left;
}
#undef f

#define f parse_additive_expr
/**
 * @brief Parses an additive expression.
 *
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 * @param index The current index.
 * @return Expr*
 */
Expr *parse_additive_expr(Token **tokens, size_t tokens_size, int *index)
{
    // Create a tmp index
    int tmp_index = *index;

    // Parse the left expression
    Expr *left = parse_multiplicative_expr(tokens, tokens_size, &tmp_index);

    // Get the current token
    Token *token = tokens[tmp_index];

    // While the current token is a plus or minus token
    while (token->type == TOKEN_TYPE_PLUS || token->type == TOKEN_TYPE_MINUS)
    {
        // Increment the index
        tmp_index++;

        // Parse the right expression
        Expr *right = parse_primary_expr(tokens, tokens_size, &tmp_index);

        // Create a new binary expression
        left = new_binary_expr(left, right, token->value);

        // Get the current token
        token = tokens[tmp_index];
    }

    // Set the index to the tmp index
    *index = tmp_index;

    // Return the left expression
    return left;
}
#undef f

#define f parse_expr
/**
 * @brief Parses an expression.
 *
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 * @param index The current index.
 * @return Expr*
 */
Expr *parse_expr(Token **tokens, size_t tokens_size, int *index)
{
    return parse_additive_expr(tokens, tokens_size, index);
}
#undef f

#define f push_back_key
/**
 * @brief Pushes back a statement to the program body.
 *
 * @param program The program.
 * @param expr The expression.
 */
void push_back_expr(Program *program, Expr *expr)
{
    // Create a tmp array
    Expr **tmp = malloc(sizeof(Expr) * (program->body_size + 1));
    // Copy the body to the tmp array
    memcpy(tmp, program->body, sizeof(Expr) * program->body_size);
    // Free the body
    free(program->body);
    // Set the body to the tmp array
    program->body = tmp;
    // Set the body at the current index to the statement
    program->body[program->body_size] = expr;
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
    program->body = malloc(sizeof(Expr) * tokens_size);
    program->body_size = 0;

    // While not EOF
    for (int i = 0; !is_eof(tokens, tokens_size, i); i++)
    {
        // Parse the statement
        Expr *expr = parse_expr(tokens, tokens_size, &i);

        // Pushback the statement to the body
        push_back_expr(program, expr);
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