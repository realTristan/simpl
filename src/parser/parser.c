#ifndef PARSER_C
#define PARSER_C

#include "../nodes/nodes.h"
#include "../lexer/lexer.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
bool is_eof(Token *tokens, size_t index, size_t tokens_size)
{
    return tokens[index].type == TOKEN_TYPE_EOF;
}
#undef f

#define f new_identifier_expr
/**
 * @brief Creates a new integer expression.
 * 
 * @param value The value of the integer.
 * @return Expr* 
 */
Expr *new_expr(char *value, NodeType type)
{
    Expr *expr = malloc(sizeof(Expr));
    expr->type = type;
    expr->value = value;
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
Expr *parse_primary_expr(Token *tokens, size_t tokens_size, size_t *index)
{
    Token token = tokens[*index];
    switch (token.type)
    {
    case TOKEN_TYPE_IDENTIFIER:
        *index += 1;
        return (Expr *)new_expr(token.value, NODE_TYPE_IDENTIFIER);
    default:
        return NULL;
    }
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
Expr *parse_expr(Token *tokens, size_t tokens_size, size_t *index)
{
    return parse_primary_expr(tokens, tokens_size, index);
}
#undef f

#define f new_expr_stmt
/**
 * @brief Creates a new expression statement.
 * 
 * @param expr The expression.
 * @return Stmt* 
 */
Stmt *new_expr_stmt(Expr *expr)
{
    Stmt *stmt = malloc(sizeof(Stmt));
    stmt->type = expr->type;
    stmt->value = expr->value;
    return stmt;
}
#undef f

#define f parse_stmt
/**
 * @brief Parses a statement.
 * 
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 * @param index The current index.
 * @return Stmt* 
 */
Stmt *parse_stmt(Token *tokens, size_t tokens_size, size_t *index)
{
    // The statement
    Stmt *stmt = malloc(sizeof(Stmt));

    // Parse the expression
    Expr *expr = parse_expr(tokens, tokens_size, index);

    // Create the expression statement
    return (Stmt *)new_expr_stmt(expr);
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
Program *parse_program(Token *tokens, size_t tokens_size)
{
    // Initialize the program
    Program *program = malloc(sizeof(Program));
    program->body = malloc(sizeof(Stmt) * tokens_size);
    program->body_size = 0;
    
    // While not EOF
    for (int i = 0; !is_eof(tokens, i, tokens_size); i++)
    {
        // Parse the statement
        Stmt *stmt = parse_stmt(tokens, tokens_size, (size_t *)&i);
        
        // Allocate more memory for the body
        program->body = realloc(program->body, sizeof(Stmt) * (program->body_size + 1));

        // Add the statement to the body
        program->body[program->body_size] = stmt;

        // Increment the body size
        program->body_size++;
    }

    return program;
}
#undef f

/**
 * @brief Parses tokens.
 * 
 * @param tokens The tokens array.
 * @param tokens_size The amount of tokens.
 */
void parser(Token *tokens, size_t tokens_size)
{
    
}

#endif // PARSER_C