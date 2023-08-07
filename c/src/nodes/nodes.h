#ifndef NODES_C
#define NODES_C

#include "node_type.h"
#include "node_structs.h"

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Creates a new expression node.
 *
 * @param type The type of the expression.
 * @param value The value of the expression.
 * @return Expr*
 */
Stmt *new_expr_stmt(NodeType type, char *value);

/**
 * @brief Creates a new binary expression node.
 *
 * @param next The next binary expression.
 * @param current The current expression.
 * @param op The operator.
 * @return Expr*
 */
Stmt *new_bin_expr_stmt(BinaryExpr *next, RegularExpr *current, char *op);

/**
 * @brief Set the stmt to binary expr object 
 * 
 * @param stmt The statement.
 * @param bin_expr The binary expression.
 */
void set_stmt_to_binary_expr(Stmt *stmt, BinaryExpr *bin_expr);

/**
 * @brief Set the stmt to expr object 
 * 
 * @param stmt The statement.
 * @param expr The expression.
 */
void set_stmt_to_expr(Stmt *stmt, RegularExpr *expr);

/**
 * @brief Frees a statement's unused memory.
 *
 * @param stmt The statement.
 * @return void
 */
void free_stmt_unused_mem(Stmt *stmt);

#endif // NODES_C