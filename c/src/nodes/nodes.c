#ifndef NODES_C
#define NODES_C

#include "node_types.h"

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
 * @return reg_expr_t
 */
reg_expr_t *new_reg_expr(node_type type, char *value)
{
    reg_expr_t *reg_expr = malloc(sizeof(reg_expr));
    reg_expr->value = value;
    reg_expr->type = type;
    return reg_expr;
}

/**
 * @brief Creates a new binary expression node.
 *
 * @param left The left binary expression.
 * @param right The right expression.
 * @param op The operator.
 * @return bin_expr_t
 */
bin_expr_t *new_bin_expr(bin_expr_t *left, reg_expr_t *right, char *op)
{
    bin_expr_t *bin_expr = malloc(sizeof(bin_expr_t));
    bin_expr->left = left;
    bin_expr->right = right;
    bin_expr->op = op;
    return bin_expr;
}

/**
 * @brief Return a new binary expression statement
 *
 * @param left The left binary expression.
 * @param right The right expression.
 * @param op The operator.
 * @return stmt_t
 */
stmt_t *new_bin_expr_stmt(bin_expr_t *left, reg_expr_t *right, char *op)
{
    // Allocate memory for the statement and set the
    // type to binary expression
    stmt_t *stmt = malloc(sizeof(stmt_t));
    stmt->type = NODE_TYPE_BINARY_EXPRESSION;

    // Set the binary expression variables
    stmt->bin_expr = malloc(sizeof(bin_expr_t));
    stmt->bin_expr->left = left;
    stmt->bin_expr->right = right;
    stmt->bin_expr->op = op;

    // Set the regular expression to NULL so we know that
    stmt->reg_expr = NULL;

    // Return the final statement
    return stmt;
}

/**
 * @brief Return a new regular expression statement
 *
 * @param type The type of the expression.
 * @param value The value of the expression.
 * @return stmt_ts
 */
stmt_t *new_reg_expr_stmt(node_type type, char *value)
{
    // Allocate memory for the statement and set the
    // type to regular expression
    stmt_t *stmt = malloc(sizeof(stmt_t));
    stmt->type = NODE_TYPE_REGULAR_EXPRESSION;

    // Set the regular expression variables
    stmt->reg_expr = malloc(sizeof(reg_expr_t));
    stmt->reg_expr->type = type;
    stmt->reg_expr->value = value;

    // Set the binary expression to NULL so we know that
    // it's not being used.
    stmt->bin_expr = NULL;

    // Return the final statement
    return stmt;
}

/**
 * @brief Set the stmt to binary expr object
 *
 * @param stmt The statement.
 * @param bin_expr The binary expression.
 */
void set_stmt_to_bin_expr(stmt_t *stmt, bin_expr_t *bin_expr)
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
void set_stmt_to_reg_expr(stmt_t *stmt, reg_expr_t *reg_expr)
{
    stmt->type = NODE_TYPE_REGULAR_EXPRESSION;
    stmt->reg_expr = reg_expr;
}

#endif // NODES_C