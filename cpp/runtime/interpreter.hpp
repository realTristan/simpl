#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "ast.hpp"
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
    if (left->type != ValueType::NUMBER || right->type != ValueType::NUMBER)
    {
      return;
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
      NumberValue *res = new NumberValue();
      res->value = left_num->value + right_num->value;
      return res;

    case '-':
      NumberValue *res = new NumberValue();
      res->value = left_num->value - right_num->value;
      return res;

    case '*':
      NumberValue *res = new NumberValue();
      res->value = left_num->value * right_num->value;
      return res;

    case '/':
      NumberValue *res = new NumberValue();
      res->value = left_num->value / right_num->value;
      return res;

    default:
      return;
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
  RuntimeValue *evalIdentifier(Identifier *node, Environment *env)
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
      return;
    }

    // Evaluate the value
    std::string name = ((Identifier *)node->assignee)->value;
    if (!env->get(name))
    {
      return;
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
    if (obj->type != ValueType::OBJECT)
    {
      return;
    }

    // Get the property
    std::string prop = ((Identifier *)node->property)->value;
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
    // Evaluate each argument
    std::vector<RuntimeValue *> args;
    for (auto arg : node->args)
    {
      args.push_back(evaluate(arg, env));
    }

    // Evaluate the function itself
    RuntimeValue *fn = evaluate(node->caller, env);

    // If unknown function
    if (fn->type == ValueType::NATIVEFN)
    {
      const NativeFnValue *func = (NativeFnValue *)fn;
      return func->call(args);
    }
    else if (fn->type == ValueType::FN)
    {
      // Create a new scope and set the func type
      FnValue *func = (FnValue *)fn;
      Environment *scope = new Environment(func->env);

      // Declare the function parameters in that scope
      for (int i = 0; i < func->params.size(); i++)
      {
        scope->declare(func->params[i], args[i], false);
      }

      // Evaluate the function body
      RuntimeValue *result = new NullValue();
      for (auto stmt : func->body)
      {
        result = evaluate(stmt, scope);
      }

      // Return the result
      return result;
    }
    else
    {
      return;
    }
  }

  /**
   * Evaluate a function declaration.
   * @param node The function declaration node.
   * @param env The environment.
   * @return The evaluated value.
  */
  RuntimeValue *evalFnDeclaration(FunctionDeclaration *node, Environment *env)
  {
    // Create the function
    FnValue *fn = new FnValue();
    fn->name = node->name;
    fn->params = node->params;
    fn->env = env;
    fn->body = node->body;

    // Declare the function
    return env->declare(node->name, fn, true);
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
      const NumericLiteral *num = (NumericLiteral *)node;
      NumberValue *res = new NumberValue();
      res->value = num->value;
      return res;

    case NodeType::NULL_LITERAL:
      return new NullValue();

    case NodeType::IDENTIFIER:
      return evalIdentifier((Identifier *)node, env);

    case NodeType::BINARY_EXPR:
      return evalBinaryExpr((BinaryExpr *)node, env);

    case NodeType::PROGRAM:
      return evalProgram((Program *)node, env);

    case NodeType::VARIABLE_DECLARATION:
      return evalVariableDeclaration((VariableDeclaration *)node, env);

    case NodeType::ASSIGNMENT_EXPR:
      return evalAssignmentExpression((AssignmentExpr *)node, env);

    case NodeType::OBJECT_LITERAL:
      return evalObjectLiteral((ObjectLiteral *)node, env);

    case NodeType::MEMBER_EXPR:
      return evalMemberExpression((MemberExpr *)node, env);

    case NodeType::CALL_EXPR:
      return evalCallExpression((CallExpr *)node, env);

    case NodeType::FUNCTION_DECLARATION:
      return evalFnDeclaration((FunctionDeclaration *)node, env);

    default:
      return;
    }
  }
};

#endif // INTERPRETER_HPP