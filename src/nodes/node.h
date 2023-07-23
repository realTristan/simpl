#ifndef NODE_H
#define NODE_H

#include "node_type.h"
#include <stdlib.h>

/**
 * @brief A statement node.
 *
 */
typedef struct Stmt
{
    NodeType type;
} Stmt;

/**
 * @brief A program node.
 *
 */
typedef struct Program
{
    NodeType NODE_TYPE_PROGRAM;
    Stmt **statements;
    size_t num_statements;
} Program;

/**
 * @brief An expression node.
 *
 */
typedef struct Expr
{
    NodeType type;
} Expr;

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
} BinaryExpr;

/**
 * @brief An identifier node.
 *
 */
typedef struct Identifier
{
    NodeType NODE_TYPE_IDENTIFIER;
    char *symbol;
} Identifier;

/**
 * @brief An numeric literal node.
 *
 */
typedef struct NumericLiteral
{
    NodeType type;
    double value;
} NumericLiteral;

#endif // NODE_H