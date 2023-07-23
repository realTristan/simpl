#ifndef NODE_H
#define NODE_H

#include "node_types.h"
#include <stdlib.h>

/**
 * @brief A statement node.
 *
 */
typedef struct Stmt
{
    NodeType type;
};

/**
 * @brief A program node.
 *
 */
typedef struct Program
{
    NodeType NODE_TYPE_PROGRAM;
    Stmt **statements;
    size_t num_statements;
};

/**
 * @brief An expression node.
 *
 */
typedef struct Expr
{
    NodeType type;
};

/**
 * @brief A binary expression node.
 *
 */
typedef struct BinaryExpr
{
    NodeType NODE_TYPE_BINARY_EXPRESSION;
    Expr *left;
    Expr *right;
    char *op;
};

/**
 * @brief An identifier node.
 *
 */
typedef struct Identifier
{
    NodeType NODE_TYPE_IDENTIFIER;
    char *symbol;
};

/**
 * @brief An numeric literal node.
 *
 */
typedef struct NumericLiteral
{
    NodeType type;
    double value;
};

#endif // NODE_H