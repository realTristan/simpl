#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "../ast.hpp"
#include "env.hpp"
#include "values.hpp"

class Interpreter
{
private:
  /**
   * Evaluate a binary expression.
   * @param node The binary expression node.
   * @param env The environment.
   * @return The evaluated value.
   */
  RuntimeValue *evalBinaryExpr(BinaryExpr *node, Environment *env)
  {
    // Get the left and right operands, evaluate them. Recursion present.
    RuntimeValue *left = evaluate(node->left, env);
    RuntimeValue *right = evaluate(node->right, env);

    // Ensure that both operands are numbers
    if (left->type != NUMBER || right->type != NUMBER)
    {
      throw std::runtime_error("Invalid operands");
    }

    // Get the left and right number values
    const NumberValue *left_num = (NumberValue *)left;
    const NumberValue *right_num = (NumberValue *)right;

    // Get the operator
    const char op = node->op;

    // Evaluate the binary expression
    switch (op)
    {
    case '+':
    {
      NumberValue *res = new NumberValue();
      res->value = left_num->value + right_num->value;
      return res;
    }

    case '-':
    {
      NumberValue *res = new NumberValue();
      res->value = left_num->value - right_num->value;
      return res;
    }

    case '*':
    {
      NumberValue *res = new NumberValue();
      res->value = left_num->value * right_num->value;
      return res;
    }

    case '/':
    {
      NumberValue *res = new NumberValue();
      res->value = left_num->value / right_num->value;
      return res;
    }

    default:
      throw std::runtime_error("Invalid operator");
    }
  }

  /**
   * Evaluate a program.
   * @param node The program node.
   * @param env The environment.
   * @return The last evaluated value.
   */
  RuntimeValue *evalProgram(Program *node, Environment *env)
  {
    // Store the last evaluated value. This will be returned.
    // Keep null as the default value.
    RuntimeValue *last = new NullValue();

    // Iterate over the body of the program
    for (auto stmt : node->body)
    {
      // Evaluate the statement
      last = evaluate(stmt, env);
    }

    // Return the last evaluated
    return last;
  }

  /**
   * Evaluate an identifier.
   * @param node The identifier node.
   * @param env The environment.
   * @return The evaluated value.
   */
  RuntimeValue *evalIdentifier(struct Identifier *node, Environment *env)
  {
    return env->get(node->value);
  }

  /**
   * Evaluate a variable declaration.
   * @param node The variable declaration node.
   * @param env The environment.
   * @return The evaluated value.
   */
  RuntimeValue *evalVariableDeclaration(VariableDeclaration *node, Environment *env)
  {
    // Evaluate the value
    RuntimeValue *value = node->value ? evaluate(node->value, env) : new NullValue();

    // Declare the variable
    return env->declare(node->identifier, value, node->constant);
  }

  /**
   * Evaluate an assignment expression.
   * @param node The assignment expression node.
   * @param env The environment.
   * @return The evaluated value.
   */
  RuntimeValue *evalAssignmentExpression(AssignmentExpr *node, Environment *env)
  {
    // If the node is not an identifier
    if (node->assignee->type != NodeType::IDENTIFIER)
    {
      throw std::runtime_error("Invalid assignment");
    }

    // Evaluate the value
    struct Identifier *assignee = (struct Identifier *)node->assignee;
    std::string name = assignee->value;
    if (!env->get(name))
    {
      throw std::runtime_error("Variable not declared");
    }

    // Assign the value
    return env->assign(name, evaluate(node->value, env));
  }

  /**
   * Evaluate an object literal.
   * @param node The object literal node.
   * @param env The environment.
   * @return The evaluated value.
   */
  RuntimeValue *evalObjectLiteral(ObjectLiteral *node, Environment *env)
  {
    // Create the object
    ObjectValue *obj = new ObjectValue();

    // Iterate over the properties
    for (auto prop : node->properties)
    {
      obj->properties[prop->key] = prop->value ? evaluate(prop->value, env) : env->get(prop->key);
    }

    // Return the object
    return obj;
  }

  /**
   * Evaluate a member expression.
   * @param node The member expression node.
   * @param env The environment.
   * @return The evaluated value.
   */
  RuntimeValue *evalMemberExpression(MemberExpr *node, Environment *env)
  {
    // Evaluate the object
    RuntimeValue *obj = evaluate(node->object, env);

    // If the object is not an object
    if (obj->type != OBJECT)
    {
      throw std::runtime_error("Invalid member expression");
    }

    // Get the property
    struct Identifier *node_prop = (struct Identifier *)node->property;
    std::string prop = node_prop->value;
    return ((ObjectValue *)obj)->properties[prop];
  }

  /**
   * Evaluate a call expression.
   * @param node The call expression node.
   * @param env The environment.
   * @return The evaluated value.
   */
  RuntimeValue *evalCallExpression(CallExpr *node, Environment *env)
  {
  }

  /**
   * Evaluate a function declaration.
   * @param node The function declaration node.
   * @param env The environment.
   * @return The evaluated value.
   */
  RuntimeValue *evalFnDeclaration(FunctionDeclaration *node, Environment *env)
  {
  }

public:
  /**
   * Evaluate a statement.
   * @param node The statement node.
   * @param env The environment.
   * @return The evaluated value.
   */
  RuntimeValue *evaluate(Stmt *node, Environment *env)
  {
    switch (node->type)
    {
    case NodeType::NUMERIC_LITERAL:
    {
      const NumericLiteral *num = (NumericLiteral *)node;
      NumberValue *res = new NumberValue();
      res->value = num->value;
      return res;
    }

    case NodeType::NULL_LITERAL:
    {
      return new NullValue();
    }

    case NodeType::IDENTIFIER:
    {
      struct Identifier *node = (struct Identifier *)node;
      return evalIdentifier(node, env);
    }

    case NodeType::BINARY_EXPR:
    {
      return evalBinaryExpr((BinaryExpr *)node, env);
    }

    case NodeType::PROGRAM:
    {
      return evalProgram((Program *)node, env);
    }

    case NodeType::VARIABLE_DECLARATION:
    {
      return evalVariableDeclaration((VariableDeclaration *)node, env);
    }

    case NodeType::ASSIGNMENT_EXPR:
    {
      return evalAssignmentExpression((AssignmentExpr *)node, env);
    }

    case NodeType::OBJECT_LITERAL:
    {
      return evalObjectLiteral((ObjectLiteral *)node, env);
    }

    case NodeType::MEMBER_EXPR:
    {
      return evalMemberExpression((MemberExpr *)node, env);
    }

    case NodeType::CALL_EXPR:
    {
      return evalCallExpression((CallExpr *)node, env);
    }

    case NodeType::FUNCTION_DECLARATION:
    {
      return evalFnDeclaration((FunctionDeclaration *)node, env);
    }

    default:
    {
      throw std::runtime_error("Invalid node type");
    }
    }
  }
};

#endif // INTERPRETER_HPP