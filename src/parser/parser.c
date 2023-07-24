#ifndef PARSER_C
#define PARSER_C

#include "../nodes/nodes.h"
#include "../lexer/lexer.h"

#include "utils.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define f new_expr_node
/**
 * @brief Creates a new expression.
 *
 * @param type The type of the expression.
 * @param token The token.
 * @return Expr*
 */
Expr *new_expr_node(NodeType type, Token *token)
{
    Expr *expr = (Expr *)malloc(sizeof(Expr));
    expr->type = type;
    expr->value = token->value;
    return expr;
}
#undef f

#define f new_bin_expr_node
/**
 * @brief Creates a new binary expression.
 *
 * @param left The left binary expression.
 * @param right The right expression.
 * @param op The operator.
 * @return Expr*
 */
BinaryExpr *new_bin_expr_node(BinaryExpr *left, Expr *right, char *op)
{
    BinaryExpr *bin_expr = (BinaryExpr *)malloc(sizeof(BinaryExpr));
    bin_expr->type = NODE_TYPE_BINARY_EXPRESSION;
    bin_expr->left = left;
    bin_expr->right = right;
    bin_expr->op = op;
    return bin_expr;
}
#undef f

/*
#define f new_identifier_node
Identifier *new_identifier_node(Token *token)
{
    Identifier *identifier = (Identifier *)malloc(sizeof(Identifier));
    identifier->type = NODE_TYPE_IDENTIFIER;
    identifier->value = token->value;
    return identifier;
}
#undef f

#define f new_numeric_literal_node
NumericLiteral *new_numeric_literal_node(Token *token)
{
    NumericLiteral *numeric_literal = (NumericLiteral *)malloc(sizeof(NumericLiteral));
    numeric_literal->type = NODE_TYPE_NUMERIC_LITERAL;
    numeric_literal->value = token->value;
    return numeric_literal;
}
#undef f
*/

#define f parse_primary_stmt
/**
 * @brief Parses a primary expression.
 *
 * @param tokens The tokens array.
 * @param index The current index.
 * @return Stmt*
 */
Stmt *parse_primary_stmt(Token **tokens, int *index)
{
    // Token and Statement pointers
    Token *token = tokens[*index];
    Stmt *stmt = malloc(sizeof(Stmt));

    // Check the token type
    switch (token->type)
    {
    case TOKEN_TYPE_IDENTIFIER:
        stmt->expr = new_expr_node(NODE_TYPE_IDENTIFIER, token);
        return stmt;
    case TOKEN_TYPE_NUMBER:
        stmt->expr = new_expr_node(NODE_TYPE_NUMERIC_LITERAL, token);
        return stmt;
    case TOKEN_TYPE_PLUS:
    case TOKEN_TYPE_MINUS:
    case TOKEN_TYPE_MULTIPLY:
    case TOKEN_TYPE_DIVIDE:
        stmt->expr = new_expr_node(NODE_TYPE_BINARY_EXPRESSION, token);
        return stmt;
    default:
        free(stmt);
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
    Stmt *res = parse_primary_stmt(tokens, index);

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
        Stmt *right = parse_primary_stmt(tokens, index);

        // Create a new binary expression
        if (res->expr != NULL)
            res->bin_expr = new_bin_expr_node(NULL, res->expr, op->value);
        res->bin_expr = new_bin_expr_node(res->bin_expr, right->expr, op->value);
        res->expr = NULL;
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
        Stmt *right = parse_primary_stmt(tokens, index);

        // Create a new binary expression
        if (res->expr != NULL)
            res->bin_expr = new_bin_expr_node(NULL, res->expr, op->value);
        res->bin_expr = new_bin_expr_node(res->bin_expr, right->expr, op->value);

        // Increment the index to go back to the middle token
        (*index)++;
    }

    // Free opposite expressions
    if (res->bin_expr != NULL)
    {
        free(res->expr);
        res->expr = NULL;
    }
    if (res->expr != NULL)
    {
        free(res->bin_expr);
        res->bin_expr = NULL;
    }

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