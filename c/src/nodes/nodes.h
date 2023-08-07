#ifndef NODES_H
#define NODES_H

#include "node_types.h"

#include <stdlib.h>

/**
 * @brief Creates a new program
 *
 */
program_t *new_program();

/**
 * @brief Creates a new expression node.
 *
 * @param type The type of the expression.
 * @param value The value of the expression.
 * @return reg_expr_t
 */
reg_expr_t *new_reg_expr(node_type type, char *value);

/**
 * @brief Creates a new binary expression node.
 *
 * @param left The left binary expression.
 * @param right The right expression.
 * @param op The operator.
 * @return bin_expr_t
 */
bin_expr_t *new_bin_expr(bin_expr_t *left, reg_expr_t *right, char *op);

/**
 * @brief Return a new binary expression statement
 *
 * @param left The left binary expression.
 * @param right The right expression.
 * @param op The operator.
 * @return stmt_t
 */
stmt_t *new_bin_expr_stmt(bin_expr_t *left, reg_expr_t *right, char *op);

/**
 * @brief Return a new regular expression statement
 *
 * @param type The type of the expression.
 * @param value The value of the expression.
 * @return stmt_ts
 */
stmt_t *new_reg_expr_stmt(node_type type, char *value);

/**
 * @brief Set the stmt to binary expr object
 *
 * @param stmt The statement.
 * @param bin_expr The binary expression.
 */
void set_stmt_to_bin_expr(stmt_t *stmt, bin_expr_t *bin_expr);

/**
 * @brief Set the stmt to expr object
 *
 * @param stmt The statement.
 * @param expr The expression.
 */
void set_stmt_to_reg_expr(stmt_t *stmt, reg_expr_t *reg_expr);

#endif // NODES_H