#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <string>

// Node type
typedef enum
{
  PROGRAM,
  VARIABLE_DECLARATION,
  FUNCTION_DECLARATION,
  ASSIGNMENT_EXPR,
  BINARY_EXPR,
  UNARY_EXPR,
  MEMBER_EXPR,
  CALL_EXPR,
  NUMERIC_LITERAL,
  NULL_LITERAL,
  IDENTIFIER,
  PROPERTY,
  OBJECT_LITERAL,
} NodeType;

// Statement interface
typedef struct Stmt
{
  NodeType type;
} Stmt;

// Expression interface that extends statement
typedef struct Expr : Stmt
{
} Expr;

// Program node
typedef struct Program : Stmt
{
  NodeType type = NodeType::PROGRAM;
  std::vector<Stmt *> body;
} Program;

// Variable declaration node
typedef struct VariableDeclaration : Stmt
{
  NodeType type = NodeType::VARIABLE_DECLARATION;
  bool constant;
  std::string identifier;
  Expr *value;
} VariableDeclaration;

// Function declaration node
typedef struct FunctionDeclaration : Stmt
{
  NodeType type = NodeType::FUNCTION_DECLARATION;
  std::string name;
  std::vector<std::string> params;
  std::vector<Stmt *> body;
} FunctionDeclaration;

// Numeric literal node
typedef struct NumericLiteral : Expr
{
  NodeType type = NodeType::NUMERIC_LITERAL;
  double value;
} NumericLiteral;

// Identifier node
typedef struct Identifier : Expr
{
  NodeType type = NodeType::IDENTIFIER;
  std::string value;
} Identifier;

// Binary expression node
typedef struct BinaryExpr : Expr
{
  NodeType type = NodeType::BINARY_EXPR;
  char op;
  struct BinaryExpr *left;
  struct Expr *right;
} BinaryExpr;

// Assignment expression node
typedef struct AssignmentExpr : Expr
{
  NodeType type = NodeType::ASSIGNMENT_EXPR;
  struct Identifier *assignee;
  Expr *value;
} AssignmentExpr;

// Call expression node
typedef struct CallExpr : Expr
{
  NodeType type = NodeType::CALL_EXPR;
  std::vector<Expr *> args;
  struct Expr *caller;
} CallExpr;

// Member expression node
typedef struct MemberExpr : Expr
{
  NodeType type = NodeType::MEMBER_EXPR;
  struct Expr *object;
  struct Expr *property;
  bool computed;
} MemberExpr;

// Unary expression node
typedef struct UnaryExpr : Expr
{
  NodeType type = NodeType::UNARY_EXPR;
  std::string op;
  Expr *argument;
} UnaryExpr;

// Null literal node
typedef struct NullLiteral : Expr
{
  NodeType type = NodeType::NULL_LITERAL;
  std::string value = "null";
} NullLiteral;

// Property node
typedef struct Property : Expr
{
  NodeType type = NodeType::PROPERTY;
  std::string key;
  Expr *value;
} Property;

// Object literal node
typedef struct ObjectLiteral : Expr
{
  NodeType type = NodeType::OBJECT_LITERAL;
  std::vector<Property *> properties;
} ObjectLiteral;

#endif // AST_HPP