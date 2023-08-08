import { ValueType, RuntimeValue, NumberValue, NullValue } from "./values.ts";
import { BinaryExpr, NodeType, NumericLiteral, Program, Stmt } from "../ast.ts";

/**
 * Evaluate a binary expression node
 * @param node the binary expression node to evaluate
 * @returns RuntimeValue
 */
function evaluateBinaryExpr(node: BinaryExpr): RuntimeValue {
  // Get the left and right operands, evaluate them. Recursion present.
  const left: RuntimeValue = evaluate(node.left);
  const right: RuntimeValue = evaluate(node.right);

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
function evaluateProgram(node: Program): RuntimeValue {
  // Store the last evaluated value. This will be returned.
  // Keep null as the default value.
  let last: RuntimeValue = {
    type: "null",
    value: "null",
  } as NullValue;

  // Iterate over the body of the program
  for (const stmt of (node as Program).body) {
    // Evaluate the statement
    last = evaluate(stmt);
  }

  // Return the last evaluated
  return last;
}

/**
 * Evaluate a node
 * @param node the node to evaluate
 * @returns RuntimeValue
 */
export function evaluate(node: Stmt): RuntimeValue {
  switch (node.type) {
    // If the provided node is a numeric literal, return a number value
    case "NumericLiteral":
      return {
        type: "number",
        value: (node as NumericLiteral).value,
      } as NumberValue;

    // If the provided node is a null literal, return a null value
    case "NullLiteral":
      return {
        type: "null",
        value: "null",
      } as NullValue;

    // If the provided node is a binary expression, evaluate it
    case "BinaryExpr":
      return evaluateBinaryExpr(node as BinaryExpr);

    // If the provided node is a program, evaluate it
    case "Program":
      return evaluateProgram(node as Program);

    // Otherwise, throw an error indicating that the provided node
    // is not a valid node type
    default:
      throw new Error(`Invalid node type: ${(node as Stmt).type}`);
  }
}
