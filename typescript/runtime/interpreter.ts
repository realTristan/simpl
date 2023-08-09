import {
  RuntimeValue,
  NumberValue,
  NULL,
  NUMBER,
  ObjectValue,
  StringValue,
} from "./values.ts";

import {
  AssignmentExpr,
  BinaryExpr,
  CallExpr,
  Identifier,
  MemberExpr,
  NumericLiteral,
  ObjectLiteral,
  Program,
  Stmt,
  VarDeclaration,
} from "../ast.ts";
import Environment from "./env.ts";

/**
 * Evaluate a binary expression node
 * @param node the binary expression node to evaluate
 * @returns RuntimeValue
 */
function evaluateBinaryExpr(node: BinaryExpr, env: Environment): RuntimeValue {
  // Get the left and right operands, evaluate them. Recursion present.
  const left: RuntimeValue = evaluate(node.left, env);
  const right: RuntimeValue = evaluate(node.right, env);

  // Ensure that both operands are numbers
  if (left.type !== "number" || right.type !== "number") {
    throw new Error("Invalid operands");
  }

  // Evaluate the binary expression
  switch (node.operator) {
    case "+":
      return {
        type: "number",
        value: (left as NumberValue).value + (right as NumberValue).value,
      } as NumberValue;

    case "-":
      return {
        type: "number",
        value: (left as NumberValue).value - (right as NumberValue).value,
      } as NumberValue;

    case "*":
      return {
        type: "number",
        value: (left as NumberValue).value * (right as NumberValue).value,
      } as NumberValue;

    case "/":
      return {
        type: "number",
        value: (left as NumberValue).value / (right as NumberValue).value,
      } as NumberValue;

    default:
      throw new Error(`Invalid operator: ${node.operator}`);
  }
}

/**
 * Evaluate a program node
 * @param node the program node to evaluate
 * @returns RuntimeValue
 */
function evaluateProgram(node: Program, env: Environment): RuntimeValue {
  // Store the last evaluated value. This will be returned.
  // Keep null as the default value.
  let last: RuntimeValue = NULL;

  // Iterate over the body of the program
  for (const stmt of (node as Program).body) {
    // Evaluate the statement
    last = evaluate(stmt, env);
  }

  // Return the last evaluated
  return last;
}

/**
 * Evaluate an identifier
 * @param node the identifier node to evaluate
 * @returns RuntimeValue
 */
function evaluateIdentifier(node: Identifier, env: Environment): RuntimeValue {
  return env.get(node.value);
}

/**
 * Evaluate a variable declaration
 * @param node the variable declaration node
 * @param env the environment
 * @returns RuntimeValue
 */
function evaluateVariableDeclaration(
  node: VarDeclaration,
  env: Environment
): RuntimeValue {
  const value = node.value ? evaluate(node.value, env) : NULL;

  return env.declare(node.identifier, value, node.constant);
}

/**
 * Evaluate an assignment expression
 * @param node the assignment expression node
 * @param env the environment
 * @returns RuntimeValue
 */
function evaluateAssignmentExpression(
  node: AssignmentExpr,
  env: Environment
): RuntimeValue {
  // If the node is not an identifier
  if (node.assignee.type !== "Identifier") {
    throw new Error("Invalid assignment target");
  }

  // Evaluate the value
  const name: string = (node.assignee as Identifier).value;
  if (!env.get(name)) {
    throw new Error(`Undefined variable: ${name}`);
  }

  // Assign the value
  return env.assign(name, evaluate(node.value, env));
}

/**
 * Evaluate an object literal
 * @param node the object literal node
 * @param env the environment
 * @returns RuntimeValue
 */
function evaluateObjectLiteral(
  node: ObjectLiteral,
  env: Environment
): RuntimeValue {
  // Create the object
  const obj: ObjectValue = {
    type: "object",
    properties: {},
  } as ObjectValue;

  // Iterate over the properties
  for (const { key, value } of node.properties) {
    obj.properties[key] = value ? evaluate(value, env) : env.get(key);
  }

  // Return the object
  return obj;
}

/**
 * Evaluate a member expression
 * @param node the member expression node
 * @param env the environment
 * @returns RuntimeValue
 */
function evaluateMemberExpression(
  node: MemberExpr,
  env: Environment
): RuntimeValue {
  return;
}

/**
 * Evaluate a call expression
 * @param node the call expression node
 * @param env the environment
 * @returns RuntimeValue
 */
function evaluateCallExpression(
  node: CallExpr,
  env: Environment
): RuntimeValue {
  return;
}

/**
 * Evaluate a node
 * @param node the node to evaluate
 * @returns RuntimeValue
 */
export function evaluate(node: Stmt, env: Environment): RuntimeValue {
  switch (node.type) {
    // If the provided node is a numeric literal, return a number value
    case "NumericLiteral":
      return NUMBER((node as NumericLiteral).value);

    // If the provided node is a null literal, return a null value
    case "NullLiteral":
      return NULL;

    // Handle an identifier
    case "Identifier":
      return evaluateIdentifier(node as Identifier, env);

    // If the provided node is a binary expression, evaluate it
    case "BinaryExpr":
      return evaluateBinaryExpr(node as BinaryExpr, env);

    // If the provided node is a program, evaluate it
    case "Program":
      return evaluateProgram(node as Program, env);

    // Incase of variable declaration
    case "VariableDeclaration":
      return evaluateVariableDeclaration(node as VarDeclaration, env);

    // Incase of assignment expression
    case "AssignmentExpr":
      return evaluateAssignmentExpression(node as AssignmentExpr, env);

    // Incase of object literal
    case "ObjectLiteral":
      return evaluateObjectLiteral(node as ObjectLiteral, env);

    // Incase of member expression
    case "MemberExpr":
      return evaluateMemberExpression(node as MemberExpr, env);

    // Incase of call expression
    case "CallExpr":
      return evaluateCallExpression(node as CallExpr, env);

    // Otherwise, throw an error indicating that the provided node
    // is not a valid node type
    default:
      throw new Error(`Invalid node type: ${(node as Stmt).type}`);
  }
}
