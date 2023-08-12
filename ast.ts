/**
 * A node type
 * @example
 * let x = 5;
 * // => Program
 * @example
 * 5
 * // => NumericLiteral
 * @example
 * x
 * // => Identifier
 */
export type NodeType =
  // Statements
  | "Program"
  | "VariableDeclaration"
  | "FunctionDeclaration"

  // Expressions
  | "AssignmentExpr"
  | "BinaryExpr"
  | "UnaryExpr"
  | "MemberExpr"
  | "CallExpr"

  // Literals
  | "NumericLiteral"
  | "NullLiteral"
  | "Identifier"
  | "Property"
  | "ObjectLiteral";

/**
 * A statement
 * @example
 * let x = 5;
 */
export interface Stmt {
  type: NodeType;
}

/**
 * A program
 * @example
 * let x = 5;
 *
 * // => Program { body: [LetStmt] }
 * @example
 */
export interface Program extends Stmt {
  type: "Program";
  body: Stmt[];
}

/**
 * Variable declaration expression
 */
export interface VarDeclaration extends Stmt {
  type: "VariableDeclaration";
  constant: boolean;
  identifier: string;
  value: Expr | undefined;
}

/**
 * Function declaration expression
 */
export interface FnDeclaration extends Stmt {
  type: "FunctionDeclaration";
  name: string;
  params: string[];
  body: Stmt[];
}

/**
 * A numeric literal
 * @example
 * 5
 * // => NumericLiteral { value: 5 }
 * @example
 * 5 + 5
 * // => BinaryExpr { operator: "+", left: NumericLiteral, right: NumericLiteral }
 */
export interface NumericLiteral extends Expr {
  type: "NumericLiteral";
  value: number;
}

/**
 * An identifier
 * @example
 * let x = 5;
 * // => Identifier { value: "x" }
 * @example
 * let add = (a, b) => a + b;
 * // => Identifier { value: "add" }
 */
export interface Identifier extends Expr {
  type: "Identifier";
  value: string;
}

/**
 * A binary expression
 * @example
 * 1 + 2
 * // => BinaryExpr { operator: "+", left: NumericLiteral, right: NumericLiteral }
 * @example
 * 1 + 2 * 3
 */
export interface Expr extends Stmt {}
export interface BinaryExpr extends Expr {
  type: "BinaryExpr";
  operator: string;
  left: Expr;
  right: Expr;
}

/**
 * An assignment expression
 * @example
 * x = 5
 * @example
 * x = add(1, 2)
 */
export interface AssignmentExpr extends Expr {
  type: "AssignmentExpr";
  assignee: Identifier;
  value: Expr;
}

/**
 * A call expression
 * @example
 * add(1, 2)
 * // => CallExpr { value: "add", params: [NumericLiteral, NumericLiteral] }
 * @example
 * add(1, add(2, 3))
 * // => CallExpr { value: "add", params: [NumericLiteral, CallExpr] }
 */
export interface CallExpr extends Expr {
  type: "CallExpr";
  args: Expr[];
  caller: Expr;
}

/**
 * A member expression
 * @example
 * x.y
 * // => MemberExpr { object: Identifier, property: Identifier }
 */
export interface MemberExpr extends Expr {
  type: "MemberExpr";
  object: Expr;
  property: Expr;
  computed: boolean;
}

/**
 * A unary expression
 * @example
 * -1
 * // => UnaryExpr { operator: "-", argument: NumericLiteral }
 * @example
 * -add(1, 2)
 * // => UnaryExpr { operator: "-", argument: CallExpr }
 */
export interface UnaryExpr extends Expr {
  type: "UnaryExpr";
  operator: string;
  argument: Stmt;
}

/**
 * A null literal
 * @example
 * null
 * // => NullLiteral
 * @example
 * let x = null;
 * // => NullLiteral
 */
export interface NullLiteral extends Expr {
  type: "NullLiteral";
  value: "null";
}

/**
 * A property
 * @example
 * { x: 5 }
 * // => Property { key: "x", value: NumericLiteral }
 */
export interface Property extends Expr {
  type: "Property";
  key: string;
  value: Expr | undefined;
}

/**
 * An object
 * @example
 * { x: 5 }
 */
export interface ObjectLiteral extends Expr {
  type: "ObjectLiteral";
  properties: Property[];
}
