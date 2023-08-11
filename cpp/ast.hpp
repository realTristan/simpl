#ifndef AST_HPP
#define AST_HPP

#include<vector>
#include<string>

// Node type
typedef enum {
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
typedef struct Stmt {
  NodeType type;
} Stmt;

// Expression interface that extends statement
typedef struct Expr : Stmt {} Expr;

// Program node
typedef struct Program : Stmt {
  NodeType type = PROGRAM;
  std::vector<Stmt*> body;
} Program;

// Variable declaration node
typedef struct VariableDeclaration : Stmt {
  NodeType type = VARIABLE_DECLARATION;
  bool constant;
  std::string identifier;
  Expr* value;
} VariableDeclaration;

// Function declaration node
typedef struct FunctionDeclaration : Stmt {
  NodeType type = FUNCTION_DECLARATION;
  std::string name;
  std::vector<std::string> params;
  std::vector<Stmt*> body;
} FunctionDeclaration;

// Numeric literal node
typedef struct NumericLiteral : Expr {
  NodeType type = NUMERIC_LITERAL;
  double value;
} NumericLiteral;

// Identifier node
typedef struct Identifier : Expr {
  NodeType type = IDENTIFIER;
  std::string value;
} Identifier;

// Binary expression node
typedef struct BinaryExpr : Expr {
  NodeType type = BINARY_EXPR;
  char op;
  BinaryExpr* left;
  Expr* right;
} BinaryExpr;

// Assignment expression node
typedef struct AssignmentExpr : Expr {
  NodeType type = ASSIGNMENT_EXPR;
  Identifier* assignee;
  Expr* value;
} AssignmentExpr;

// Call expression node
typedef struct CallExpr : Expr {
  NodeType type = CALL_EXPR;
  std::vector<Expr*> args;
  Expr* caller;
} CallExpr;

// Member expression node
typedef struct MemberExpr : Expr {
  NodeType type = MEMBER_EXPR;
  Expr* object;
  Expr* property;
  bool computed;
} MemberExpr;

// Unary expression node
typedef struct UnaryExpr : Expr {
  NodeType type = UNARY_EXPR;
  std::string op;
  Expr* argument;
} UnaryExpr;

// Null literal node
typedef struct NullLiteral : Expr {
  NodeType type = NULL_LITERAL;
  std::string value = "null";
} NullLiteral;

// Property node
typedef struct Property : Expr {
  NodeType type = PROPERTY;
  std::string key;
  Expr* value;
} Property;

// Object literal node
typedef struct ObjectLiteral : Expr {
  NodeType type = OBJECT_LITERAL;
  std::vector<Property*> properties;
} ObjectLiteral;

#endif // AST_HPP