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
  | "Program"
  | "NumericLiteral"
  | "NullLiteral"
  | "Identifier"
  | "BinaryExpr"
  | "CallExpr"
  | "UnaryExpr";

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
 * A numeric literal
 * @example
 * 5
 * // => NumericLiteral { value: 5 }
 * @example
 * 5 + 5
 * // => BinaryExpr { operator: "+", left: NumericLiteral, right: NumericLiteral }
 */
export interface NumericLiteral extends Stmt {
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
export interface Identifier extends Stmt {
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
export interface Expr extends Stmt {
  type: NodeType;
  value: number | string;
}
export interface BinaryExpr extends Expr {
  type: "BinaryExpr";
  operator: string;
  left: Expr;
  right: Expr;
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
export interface CallExpr extends Stmt {
  type: "CallExpr";
  value: string;
  params: Stmt[];
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
export interface UnaryExpr extends Stmt {
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
export interface NullLiteral extends Stmt {
  type: "NullLiteral";
  value: "null";
}