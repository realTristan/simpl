#ifndef NODES_C
#define NODES_C

#include "node_types.h"

#include <stdbool.h>
#include <stdlib.h>

#define NULL ((void *)0)

/**
 * @brief Creates a new program
 *
 */
program_t *new_program()
{
    program_t *program = malloc(sizeof(program_t));
    program->type = NODE_TYPE_PROGRAM;
    program->body = (stmt_array_t){malloc(sizeof(stmt_t)), (size_t)0};
    return program;
}

/**
 * @brief Creates a new expression node.
 *
 * @param type The type of the expression.
 * @param value The value of the expression.
 * @return stmt_t
 */
stmt_t new_expr_stmt(node_type type, char *value)
{
    return (stmt_t){
        NODE_TYPE_REGULAR_EXPRESSION,
        {type, value}};
}

/**
 * @brief Creates a new binary expression node.
 *
 * @param left The left binary expression.
 * @param right The right expression.
 * @param op The operator.
 * @return stmt_t
 */
stmt_t new_bin_expr_stmt(bin_expr_t *left, reg_expr_t *right, char *op)
{
    return (stmt_t){
        .type = NODE_TYPE_BINARY_EXPRESSION,
        .bin_expr = {
            .left = left,
            .right = right,
            .op = op}};
}

/**
 * @brief Set the stmt to binary expr object
 *
 * @param stmt The statement.
 * @param bin_expr The binary expression.
 */
void set_stmt_to_bin_expr(stmt_t *stmt, bin_expr_t bin_expr)
{
    stmt->type = NODE_TYPE_BINARY_EXPRESSION;
    stmt->bin_expr = bin_expr;
}

/**
 * @brief Set the stmt to expr object
 *
 * @param stmt The statement.
 * @param expr The expression.
 */
void set_stmt_to_reg_expr(stmt_t *stmt, reg_expr_t reg_expr)
{
    stmt->type = NODE_TYPE_REGULAR_EXPRESSION;
    stmt->expr = reg_expr;
}

#endif // NODES_C