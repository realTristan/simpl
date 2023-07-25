#ifndef NODE_STRUCTS_H
#define NODE_STRUCTS_H

#include "node_type.h"
#include <stdlib.h>

/**
 * @brief An expression node.
 *
 */
typedef struct RegularExpr
{
    NodeType type; // SO FAR ONLY: NODE_TYPE_NUMERIC_LITERAL || NODE_TYPE_IDENTIFIER
    char *value;
} RegularExpr;

/**
 * @brief A binary expression node.
 * @type NODE_TYPE_BINARY_EXPRESSION
 *
 */
typedef struct BinaryExpr
{
    struct BinaryExpr *next;
    struct RegularExpr *current;
    char *op;
} BinaryExpr;

/**
 * @brief A statement node.
 *
 */
typedef struct Stmt
{
    NodeType type; // NODE_TYPE_BINARY_EXPRESSION || NODE_TYPE_REGULAR_EXPRESSION
    struct RegularExpr *expr;
    struct BinaryExpr *bin_expr;
} Stmt;

/**
 * @brief A program node.
 * @type NODE_TYPE_PROGRAM
 *
 */
typedef struct Program
{
    NodeType type; // NODE_TYPE_PROGRAM
    Stmt **body;
    size_t body_size;
} Program;

#endif // NODES_STRUCTS_H