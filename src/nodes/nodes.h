#ifndef NODES_H
#define NODES_H

#include "node_type.h"
#include <stdlib.h>
/*
typedef struct NumericLiteral
{
    NodeType type; // NODE_TYPE_NUMERIC_LITERAL
    char *value;
} NumericLiteral;

typedef struct Identifier
{
    NodeType type; // NODE_TYPE_IDENTIFIER
    char *value;
} Identifier;
*/

/**
 * @brief An expression node.
 *
 */
typedef struct Expr
{
    NodeType type; // NODE_TYPE_EXPRESSION
    char *value;
} Expr;

/**
 * @brief A binary expression node.
 *
 */
typedef struct BinaryExpr
{
    NodeType type; // NODE_TYPE_BINARY_EXPRESSION

    struct BinaryExpr *left;
    struct Expr *right;

    char *op;
} BinaryExpr;

/**
 * @brief A statement node.
 *
 */
typedef struct Stmt
{
    struct Expr *expr;
    struct BinaryExpr *bin_expr;
    // struct NumericLiteral *numeric_literal;
    // struct Identifier *identifier;
} Stmt;

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