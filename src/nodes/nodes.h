#ifndef NODES_H
#define NODES_H

#include "node_type.h"
#include <stdlib.h>

/**
 * @brief An expression node.
 *
 */
typedef struct Expr {
    // Main Expression Values
    NodeType type;
    char *value;

    // Binary Expressions
    struct Expr *left;
    struct Expr *right;
    char *op;
} Expr;

/**
 * @brief A program node.
 *
 */
typedef struct Program
{
    NodeType type; // NODE_TYPE_PROGRAM
    Expr **body;
    size_t body_size;
} Program;

#endif // NODES_H