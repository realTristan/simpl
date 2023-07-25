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
Stmt *new_expr_stmt(NodeType type, char *value)
{
    Stmt *stmt = (Stmt *)malloc(sizeof(Stmt));
    stmt->type = NODE_TYPE_REGULAR_EXPRESSION;
    stmt->expr = (RegularExpr *)malloc(sizeof(RegularExpr));
    stmt->expr->value = value;
    stmt->expr->type = type;
    return stmt;
}

/**
 * @brief Creates a new binary expression node.
 *
 * @param next The next binary expression.
 * @param current The current expression.
 * @param op The operator.
 * @return Expr*
 */
Stmt *new_bin_expr_stmt(BinaryExpr *next, RegularExpr *current, char *op)
{
    Stmt *stmt = (Stmt *)malloc(sizeof(Stmt));
    stmt->type = NODE_TYPE_BINARY_EXPRESSION;
    stmt->bin_expr = (BinaryExpr *)malloc(sizeof(BinaryExpr));
    stmt->bin_expr->next = next;
    stmt->bin_expr->current = current;
    stmt->bin_expr->op = op;
    return stmt;
}

/**
 * @brief Set the stmt to binary expr object 
 * 
 * @param stmt The statement.
 * @param bin_expr The binary expression.
 */
void set_stmt_to_binary_expr(Stmt *stmt, BinaryExpr *bin_expr)
{
    stmt->type = NODE_TYPE_BINARY_EXPRESSION;
    stmt->bin_expr = bin_expr;
    // free(stmt->expr);
    stmt->expr = NULL;
}

/**
 * @brief Set the stmt to expr object 
 * 
 * @param stmt The statement.
 * @param expr The expression.
 */
void set_stmt_to_expr(Stmt *stmt, RegularExpr *expr)
{
    stmt->type = NODE_TYPE_REGULAR_EXPRESSION;
    stmt->expr = expr;
    // free(stmt->bin_expr);
    stmt->bin_expr = NULL;
}

/**
 * @brief Frees a statement's unused memory.
 *
 * @param stmt The statement.
 * @return void
 */
void free_stmt_unused_mem(Stmt *stmt)
{
    if (stmt->type == NODE_TYPE_REGULAR_EXPRESSION)
        free(stmt->expr);
    
    else if (stmt->type == NODE_TYPE_BINARY_EXPRESSION)
        free(stmt->bin_expr);
}

#endif // NODES_C