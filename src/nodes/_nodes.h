#ifndef NODES_H
#define NODES_H

#include "node_type.h"
#include <stdlib.h>

/**
 * @brief An expression node.
 *
 */
typedef struct Stmt
{
    NodeType type;
    char *value;
    double number;
} Stmt;

/**
 * @brief A binary expression node.
 *
 */
typedef struct BinaryExpr
{
    NodeType type; // NODE_TYPE_BINARY_EXPRESSION
    Stmt *left;
    Stmt *right;
    char *op;
} BinaryExpr;

/**
 * @brief A statement node.
 *
 */
typedef struct Expr
{
    struct Stmt *stmt;
    BinaryExpr *binary_expr;
} Expr;

/**
 * @brief A program node.
 *
 */
typedef struct Program
{
    NodeType type; // NODE_TYPE_PROGRAM
    Stmt **body;
    size_t body_size;
} Program;

#endif // NODES_H