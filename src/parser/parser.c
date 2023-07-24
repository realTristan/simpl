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

#define f new_identifier_node
/**
 * @brief Creates a new identifier node.
 *
 * @param token The token.
 * @return Identifier*
 */
Identifier *new_identifier_node(Token *token)
{
    Identifier *identifier = (Identifier *)malloc(sizeof(Identifier));
    identifier->type = NODE_TYPE_IDENTIFIER;
    identifier->value = token->value;
    return identifier;
}
#undef f

#define f new_numeric_literal_node
/**
 * @brief Creates a new numeric literal node.
 *
 * @param token The token.
 * @return NumericLiteral*
 */
NumericLiteral *new_numeric_literal_node(Token *token)
{
    NumericLiteral *numeric_literal = (NumericLiteral *)malloc(sizeof(NumericLiteral));
    numeric_literal->type = NODE_TYPE_NUMERIC_LITERAL;
    numeric_literal->value = token->value;
    return numeric_literal;
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
        return new_expr_node(NODE_TYPE_IDENTIFIER, token);
    case TOKEN_TYPE_NUMBER:
        return new_expr_node(NODE_TYPE_NUMERIC_LITERAL, token);
    case TOKEN_TYPE_PLUS:
    case TOKEN_TYPE_MINUS:
    case TOKEN_TYPE_MULTIPLY:
    case TOKEN_TYPE_DIVIDE:
        return new_expr_node(NODE_TYPE_BINARY_EXPRESSION, token);
    default:
        NULL;
    }
    return NULL;
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
Stmt *parse_multiplicative_stmt(Token **tokens, size_t tokens_size, int *index)
{
    // Create a tmp index
    int tmp_index = *index;

    // Create a new statement
    Stmt *res = malloc(sizeof(Stmt));
    res->expr = parse_primary_expr(tokens, tokens_size, &tmp_index);

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
        if (res->bin_expr != NULL)
        {
            res->bin_expr = new_bin_expr_node(
                res->bin_expr, right, token->value);
        }
        else if (res->expr != NULL)
        {
            BinaryExpr *tmp = new_bin_expr_node(
                NULL, res->expr, token->value);
            res->bin_expr = new_bin_expr_node(
                tmp, right, token->value);
            res->expr = NULL;
        }

        // Get the current token
        token = tokens[tmp_index];
    }

    // Set the index to the tmp index
    *index = tmp_index;

    // Return the left expression
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
Stmt *parse_additive_stmt(Token **tokens, size_t tokens_size, int *index)
{
    // Create a tmp index
    int tmp_index = *index;

    // Parse the initial statement
    Stmt *res = parse_multiplicative_stmt(tokens, tokens_size, &tmp_index);

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
        if (res->bin_expr != NULL)
        {
            res->bin_expr = new_bin_expr_node(
                res->bin_expr, right, token->value);
        }
        else if (res->expr != NULL)
        {
            BinaryExpr *tmp = new_bin_expr_node(
                NULL, res->expr, token->value);
            res->bin_expr = new_bin_expr_node(
                tmp, right, token->value);
            res->expr = NULL;
        }

        // Get the current token
        token = tokens[tmp_index];
    }

    // Set the index to the tmp index
    *index = tmp_index + 1;

    // Free opposite expressions
    if (res->bin_expr != NULL)
        free(res->expr);

    if (res->expr != NULL)
        free(res->bin_expr);

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
Stmt *parse_stmt(Token **tokens, size_t tokens_size, int *index)
{
    return parse_additive_stmt(tokens, tokens_size, index);
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
    while (!is_eof(tokens, tokens_size, index))
    {
        // Parse the statement
        Stmt *stmt = parse_stmt(tokens, tokens_size, &index);

        // Pushback the statement to the body
        push_back_stmt(program, stmt);
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