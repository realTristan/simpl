#ifndef PARSER_C
#define PARSER_C

#include "../nodes/node_types.h"
#include "../nodes/nodes.h"
#include "../lexer/lexer.h"
#include "../tokens/token.h"
#include "../tokens/token_array.h"

#include "print.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define NULL ((void *)0)

// Function declarations
stmt_t *parse_stmt(token_array_t *token_array, int *parsing_index);

#define f parse_token_stmt_handle_paren
/**
 * @brief Handles a parenthesized expression.
 *
 * @param token_array The tokens array.
 * @param parsing_index The parsing index.
 * @return stmt_t
 */
stmt_t *parse_token_stmt_handle_paren(token_array_t *token_array, int *parsing_index)
{
    // Increment the index
    (*parsing_index)++;

    // Parse the expression
    stmt_t *stmt = parse_stmt(token_array, parsing_index);

    // If the right token is not a right paranthesis, throw an error
    if (token_array->tokens[*parsing_index].type != TOKEN_TYPE_RIGHT_PAREN)
    {
        printf("Expected a right paranthesis, got %s\n", token_array->tokens[*parsing_index].value);
        exit(1);
    }

    // Return the statement
    return stmt;
}
#undef f

#define f parse_token_stmt
/**
 * @brief Parses a primary expression.
 *
 * @param token_array The tokens array.
 * @param parsing_index The parsing index.
 * @return stmt_t
 */
stmt_t *parse_token_stmt(token_array_t *token_array, int *parsing_index)
{
    // Get the right token
    token_t token = token_array->tokens[*parsing_index];

    // Check the token type
    switch (token.type)
    {
    // These return a NODE_TYPE_REGULAR_EXPRESSION Statement
    // This is used for determining (so far) how to print the stmt
    case TOKEN_TYPE_IDENTIFIER:
        // The provided type gets set to the stmt->expr->type
        // This will be used when walking the AST
        return new_reg_expr_stmt(NODE_TYPE_IDENTIFIER, token.value);
    case TOKEN_TYPE_NUMBER:
        return new_reg_expr_stmt(NODE_TYPE_NUMERIC_LITERAL, token.value);

    // NULL Literal
    case TOKEN_TYPE_NULL:
        return new_reg_expr_stmt(NODE_TYPE_NULL_LITERAL, token.value);

    // These return a NODE_TYPE_BINARY_EXPRESSION Statement
    case TOKEN_TYPE_PLUS:
    case TOKEN_TYPE_MINUS:
    case TOKEN_TYPE_MULTIPLY:
    case TOKEN_TYPE_DIVIDE:
    {
        reg_expr_t *right = new_reg_expr(NODE_TYPE_NUMERIC_LITERAL, token.value);
        return new_bin_expr_stmt(NULL, right, token.value);
    }

    // If there's an open paranthesis, parse the expression inside
    case TOKEN_TYPE_LEFT_PAREN:
        return parse_token_stmt_handle_paren(token_array, parsing_index);
    default:
        return new_reg_expr_stmt(NODE_TYPE_UNKNOWN, NULL);
    }
}
#undef f

#define f parse_multiplicative_stmt
/**
 * @brief Parses a multiplicative expression.
 *
 * @param token_array The tokens array.
 * @param parsing_index The parsing index.
 * @return stmt_t
 */
stmt_t *parse_multiplicative_stmt(token_array_t *token_array, int *parsing_index)
{
    // Get the first token
    stmt_t *res = parse_token_stmt(token_array, parsing_index);

    // While (true)
    for (;;)
    {
        // Increment the index to get the middle token
        (*parsing_index)++;

        // Get the right token
        token_t op = token_array->tokens[*parsing_index];
        if (op.type != TOKEN_TYPE_MULTIPLY && op.type != TOKEN_TYPE_DIVIDE)
            break;

        // Increment the index to get the left token
        (*parsing_index)++;

        // Parse the left token
        stmt_t *right = parse_token_stmt(token_array, parsing_index);

        // Set to a binary expression
        if (res->type == NODE_TYPE_REGULAR_EXPRESSION)
        {
            bin_expr_t *bin_expr = new_bin_expr(NULL, res->reg_expr, NULL);
            set_stmt_to_bin_expr(res, bin_expr);
        }

        // Update the binary expression
        res->bin_expr = new_bin_expr(res->bin_expr, right->reg_expr, op.value);
    }

    // Return the result statement
    return res;
}
#undef f

#define f parse_additive_stmt
/**
 * @brief Parses an additive expression.
 *
 * @param token_array The tokens array.
 * @param parsing_index The parsing index.
 * @return stmt_t
 */
stmt_t *parse_additive_stmt(token_array_t *token_array, int *parsing_index)
{
    // Get the first token
    stmt_t *res = parse_multiplicative_stmt(token_array, parsing_index);

    // While (true)
    for (;;)
    {
        // Get the right token
        token_t op = token_array->tokens[*parsing_index];
        if (op.type != TOKEN_TYPE_PLUS && op.type != TOKEN_TYPE_MINUS)
            break;

        // Increment the index to get the left token
        (*parsing_index)++;

        // Parse the left token
        stmt_t *right = parse_token_stmt(token_array, parsing_index);

        // Set to a binary expression
        if (res->type == NODE_TYPE_REGULAR_EXPRESSION)
        {
            bin_expr_t *bin_expr = new_bin_expr(NULL, res->reg_expr, NULL);
            set_stmt_to_bin_expr(res, bin_expr);
        }

        // Update the binary expression
        res->bin_expr = new_bin_expr(res->bin_expr, right->reg_expr, op.value);

        // Increment the index to go back to the middle token
        (*parsing_index)++;
    }

    // Print the resulting binary expression
    // printf("Resulting binary expression: ");
    // printf("\n%s %s %s\n", res->bin_expr->left->right->value, res->bin_expr->op, res->bin_expr->right->value);

    
    // Return the result statement
    return res;
}
#undef f

#define f parse_stmt
/**
 * @brief Parses a statement
 *
 * @param token_array The tokens array.
 * @param parsing_index The parsing index.
 * @return stmt_t
 */
stmt_t *parse_stmt(token_array_t *token_array, int *parsing_index)
{
    return parse_additive_stmt(token_array, parsing_index);
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
void push_back_stmt(program_t *program, stmt_t *stmt)
{
    program->body.values[program->body.size] = stmt;
    program->body.size++;
}
#undef f

#define f parse_program
/**
 * @brief Parses a program.
 *
 * @param token_array The tokens array.
 * @return program_t*
 */
program_t *parse_program(token_array_t *token_array)
{
    // Initialize the program
    program_t *program = new_program();

    // While not EOF
    for (int i = 0; i < token_array->size; i++)
    {
        // Parse the statement
        stmt_t *stmt = parse_stmt(token_array, &i);

        // Pushback the statement to the body
        push_back_stmt(program, stmt);
    }

    // Return the program
    return program;
}
#undef f

/**
 * @brief Parses tokens.
 *
 * @param token_array The tokens array.
 * @return void
 */
void parse(token_array_t *token_array)
{
    program_t *program = parse_program(token_array);
    print_program(program); // Find a way to fix this...
}

#endif // PARSER_C