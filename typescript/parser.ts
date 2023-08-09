import {
  AssignmentExpr,
  BinaryExpr,
  CallExpr,
  Expr,
  FnDeclaration,
  Identifier,
  MemberExpr,
  NodeType,
  NullLiteral,
  NumericLiteral,
  ObjectLiteral,
  Program,
  Property,
  Stmt,
  VarDeclaration,
} from "./ast.ts";
import { Token, TokenType, tokenize } from "./lexer.ts";

/**
 * A parser
 */
export default class Parser {
  // The tokens to parse
  private tokens: Token[] = [];

  /**
   * Expect a token
   * @param token the token to expect
   * @param type the type of token
   * @param error the error to throw if the token is invalid
   * @returns boolean
   */
  private expect = (
    token: Token | Expr,
    type: TokenType | NodeType,
    error: string
  ): boolean => {
    if (token && token.type !== type) throw new Error(error);
    return true;
  };

  /**
   * Get the current token
   * @returns Token
   */
  private get currentToken(): Token {
    return this.tokens[0];
  }

  /**
   * Check if the current token is additive
   * @returns boolean
   */
  private get currentTokenIsAdditive(): boolean {
    return (
      this.currentToken.type === TokenType.BinaryOperator &&
      (this.currentToken.value === "+" || this.currentToken.value === "-")
    );
  }

  /**
   * Check if the current token is multiplicative
   * @returns boolean
   */
  private get currentTokenIsMultiplicative(): boolean {
    return (
      this.currentToken.type === TokenType.BinaryOperator &&
      (this.currentToken.value === "*" ||
        this.currentToken.value === "/" ||
        this.currentToken.value === "%")
    );
  }

  /**
   * Produce a program from source code
   * @param src the source code
   * @returns Program
   */
  public parse(src: string): Program {
    // Convert the source into tokens
    this.tokens = tokenize(src);

    // Create a program
    const program: Program = {
      type: "Program",
      body: [],
    };

    // While there are still tokens to parse
    while (this.tokens.length > 0) {
      const stmt: Stmt = this.parseStmt();
      program.body.push(stmt);
    }

    // Return the program
    return program;
  }

  /**
   * Parse a variable declaration
   * @note (const / let) identifier; or ident = expr;
   * @returns Sttmt
   */
  private parseVariableDeclaration(): Stmt {
    // Get whether an immutable assignment
    const isConst: boolean = this.tokens.shift().type == TokenType.Const;

    // Get the variable name (Identifier)
    const identifier: Token = this.tokens.shift();
    this.expect(identifier, TokenType.Identifier, "Expected identifier");

    // Get the next value after the indentifier. This can either be a semicolon
    // Example: const var;
    // Or if the next is an equals: const var = value;
    const next: Token = this.tokens.shift();

    // If the next token is a semi colon, then we are done
    if (next && next.type == TokenType.Semicolon) {
      return {
        type: "VariableDeclaration",
        identifier: identifier.value,
        constant: isConst,
      } as VarDeclaration;
    }

    // Make sure the next token is an equals for variable assignment.
    if (next.type !== TokenType.Equals)
      throw new Error("Expected variable assignment");

    // Get the declaration
    const declaration = {
      type: "VariableDeclaration",
      value: this.parseExpr(),
      identifier: identifier.value,
      constant: isConst,
    } as VarDeclaration;

    // Verify that the final token is a semicolon to signal the line close.
    // const end: Token = this.tokens.shift();
    // this.expect(end, TokenType.Semicolon, "Expected semicolon");

    // Return the declaration
    return declaration;
  }

  /**
   * Parse a function declaration
   * @returns Stmt
   */
  parseFunctionDeclaration(): Stmt {
    // Shift past the fn
    this.tokens.shift();

    // Get the function name
    const name: Token = this.tokens.shift();
    this.expect(name, TokenType.Identifier, "Expected identifier");

    const args: Expr[] = this.parseArgs();
    const params: string[] = [];
    for (const arg of args) {
      if (arg.type !== "Identifier") {
        throw new Error("Invalid function argument");
      }
      params.push((arg as Identifier).value);
    }

    // Verify that the next token is an open brace
    const openBrace: Token = this.tokens.shift();
    this.expect(openBrace, TokenType.OpenBrace, "Expected open brace");

    // Store the body
    const body: Stmt[] = [];
    while (
      this.tokens.length > 0 &&
      this.currentToken &&
      this.currentToken.type !== TokenType.CloseBrace
    ) {
      body.push(this.parseStmt());
    }

    // Expect a closing brace
    const closeBrace: Token = this.tokens.shift();
    this.expect(closeBrace, TokenType.CloseBrace, "Expected close brace");

    // If the next token is a semicolon and we're not in a 
    // variable declaration, move past it
    // if (this.currentToken && this.currentToken.type === TokenType.Semicolon)
    //  this.tokens.shift();

    // Return the fn
    return {
      type: "FunctionDeclaration",
      name: name.value,
      params: params,
      body,
    } as FnDeclaration;
  }

  /**
   * Parse a statement
   * @returns Stmt
   */
  private parseStmt(): Stmt {
    switch (this.currentToken.type) {
      case TokenType.Let:
      case TokenType.Const:
        return this.parseVariableDeclaration();

      case TokenType.Function:
        return this.parseFunctionDeclaration();

      default:
        return this.parseExpr();
    }
  }

  /**
   * Parse an expression
   * @returns Expr
   */
  private parseExpr(): Expr {
    return this.parseAssignmentExpr();
  }

  /**
   * Parse an assignment expression
   * @returns Expr
   */
  private parseAssignmentExpr(): Expr {
    // Get the left side of the expression
    let left: Expr | BinaryExpr = this.parseObjectExpr();

    // Check if the current token is an equals
    if (this.currentToken && this.currentToken.type === TokenType.Equals) {
      // Move past the equals token
      this.tokens.shift();

      // Allow for assignment chaining
      const value = this.parseAssignmentExpr();

      // Make sure the end is a semicolon
      const end: Token = this.tokens.shift();
      this.expect(end, TokenType.Semicolon, "Expected semicolon");

      // Return the assignment expression
      return {
        type: "AssignmentExpr",
        assignee: left,
        value: value,
      } as AssignmentExpr;
    }

    // Return the left side
    return left;
  }

  /**
   * Parse an object expression
   * @returns Expr
   */
  private parseObjectExpr(): Expr {
    // If the start of an object expression
    if (this.currentToken && this.currentToken.type !== TokenType.OpenBrace)
      return this.parseAdditiveExpr();

    // Move past the open brace
    this.tokens.shift();

    // Create an array of properties
    const properties: Property[] = [];

    // While there are still tokens to parse
    while (
      this.tokens.length > 0 &&
      this.currentToken &&
      this.currentToken.type !== TokenType.CloseBrace
    ) {
      // Get the object key
      const key: Token = this.tokens.shift();
      this.expect(key, TokenType.Identifier, "Expected identifier");

      // Get the next token
      const next: Token = this.tokens.shift();

      // If the next is a comma
      if (
        next &&
        (next.type === TokenType.Comma || next.type === TokenType.CloseBrace)
      ) {
        // Add the property
        properties.push({
          type: "Property",
          key: key.value,
        } as Property);

        // Continue the loop
        continue;
      }

      // If the next is a colon
      this.expect(next, TokenType.Colon, "Expected colon");

      // Add the property
      properties.push({
        type: "Property",
        key: key.value,
        value: this.parseExpr(),
      } as Property);

      // Get the next token
      const closing: Token = this.tokens.shift();

      // If the next is a comma
      if (
        closing &&
        (closing.type === TokenType.Comma ||
          closing.type === TokenType.CloseBrace)
      )
        continue;
    }

    // Make sure the end is a close brace or a comma
    const end: Token = this.tokens.shift();
    if (
      end &&
      end.type !== TokenType.CloseBrace &&
      end.type !== TokenType.Comma
    ) {
      throw new Error("Expected close brace or comma");
    }

    // Return the object expression
    return {
      type: "ObjectLiteral",
      properties: properties,
    } as ObjectLiteral;
  }

  /**
   * Parse a bianry expression
   * @returns Expr
   */
  private parseAdditiveExpr(): Expr {
    // Get the left side of the expression
    let left: Expr | BinaryExpr = this.parseMultiplicativeExpr();

    // While there are still tokens to parse
    while (this.tokens.length > 0 && this.currentTokenIsAdditive && left) {
      // Get the expression operator
      const op: Token = this.tokens.shift();

      // Get the right side of the expression
      const right: Expr = this.parseMultiplicativeExpr();

      // Create a binary expression
      const binexpr: BinaryExpr = {
        type: "BinaryExpr",
        operator: op.value,
        left: left,
        right: right,
      } as BinaryExpr;

      // Set the left to the new binary expression
      left = binexpr;
    }

    // Return the left side of the expression. We do this because
    // the left side becomes the entire binary expression
    return left;
  }

  /**
   * Parse a multiplicative expression
   * @returns Expr
   */
  private parseMultiplicativeExpr(): Expr {
    // Get the left side of the expression
    let left: Expr | BinaryExpr = this.parseCallMemberExpr();

    // While there are still tokens to parse
    while (
      this.tokens.length > 0 &&
      this.currentTokenIsMultiplicative &&
      left
    ) {
      // Get the expression operator
      const op: Token = this.tokens.shift();

      // Get the right side of the expression
      const right: Expr = this.parseCallMemberExpr();

      // Create a binary expression
      const binexpr: BinaryExpr = {
        type: "BinaryExpr",
        operator: op.value,
        left: left,
        right: right,
      } as BinaryExpr;

      // Set the left to the new binary expression
      left = binexpr;
    }

    // Return the left side of the expression. We do this because
    // the left side becomes the entire binary expression
    return left;
  }

  /**
   * Parse a call member expression
   * @returns Expr
   */
  private parseCallMemberExpr(): Expr {
    const member: Expr = this.parseMemberExpr();
    if (this.currentToken && this.currentToken.type === TokenType.OpenParen)
      return this.parseCallExpr(member);
    return member;
  }

  /**
   * Parse a call expression
   * @returns Expr
   */
  private parseCallExpr(caller: Expr): Expr {
    let callExpr: Expr = {
      type: "CallExpr",
      caller: caller,
      args: this.parseArgs(),
    } as CallExpr;

    // If open paren
    if (this.currentToken && this.currentToken.type === TokenType.OpenParen) {
      callExpr = this.parseCallExpr(callExpr);
    }

    // Return the call expression
    return callExpr;
  }

  /**
   * Parse arguments
   * @returns Expr[]
   */
  private parseArgs(): Expr[] {
    // Make sure the next token is an open paren
    const openParen: Token = this.tokens.shift();
    this.expect(openParen, TokenType.OpenParen, "Expected open paren");

    // Create an array of arguments
    const args: Expr[] = [];

    // While there are still tokens to parse
    while (
      this.tokens.length > 0 &&
      this.currentToken &&
      this.currentToken.type !== TokenType.CloseParen
    ) {
      args.push(this.parseAssignmentExpr());

      // If the next token is a closing paren
      const next: Token = this.tokens.shift();
      if (next && next.type === TokenType.CloseParen) {
        // If the next token is a semicolon, break
        // if (this.currentToken && this.currentToken.type === TokenType.Semicolon)
        //   this.tokens.shift();
        break;
      }
    }

    // Return the arguments
    return args;
  }

  /**
   * Parse a member expression
   * @returns Expr
   */
  private parseMemberExpr(): Expr {
    let object: Expr = this.parsePrimaryExpr();

    // If the current token is a dot or open bracket
    while (
      this.currentToken &&
      (this.currentToken.type === TokenType.Dot ||
        this.currentToken.type === TokenType.OpenBracket)
    ) {
      // Get the operator
      const op: Token = this.tokens.shift();

      // Non computed
      if (op.type === TokenType.Dot) {
        const property: Expr = this.parsePrimaryExpr();

        // Expect an identifier
        this.expect(property, "Identifier", "Expected identifier");

        // Update the object
        object = {
          type: "MemberExpr",
          object: object,
          property: property,
          computed: false,
        } as MemberExpr;
      }

      // Computed
      else {
        // Get the closing bracket
        const bracket: Token = this.tokens.shift();
        this.expect(bracket, TokenType.CloseBracket, "Expected close bracket");

        // Update the object
        object = {
          type: "MemberExpr",
          object: object,
          property: this.parseExpr(),
          computed: true,
        } as MemberExpr;
      }
    }

    // Return the object
    return object;
  }

  /**
   * Handle a parenthesis
   * @returns Expr
   */
  private handleParen(): Expr {
    // Parse the expression without the open paren
    const expr: Expr = this.parseExpr();

    // Get the close paren and make sure it's valid. If it's
    // not, throw an error.
    const closeParen: Token = this.tokens.shift();
    this.expect(closeParen, TokenType.CloseParen, "Expected close paren");

    // Return the expression
    return expr;
  }

  /**
   * Parse a primary expression
   * @returns Expr
   */
  private parsePrimaryExpr(): Expr {
    const token: Token = this.tokens.shift();

    switch (token.type) {
      // Numeric Literal Expression
      case TokenType.Number:
        return {
          type: "NumericLiteral",
          value: parseFloat(token.value),
        } as NumericLiteral;

      // Identifier Expression
      case TokenType.Identifier:
        return {
          type: "Identifier",
          value: token.value,
        } as Identifier;

      // Null Literal Expression
      case TokenType.Null:
        return {
          type: "NullLiteral",
          value: null,
        } as NullLiteral;

      // Handle the open paren
      case TokenType.OpenParen:
        return this.handleParen();

      // Error
      default:
        throw new Error(`Unexpected token ${token.value} (${token.type})`);
    }
  }
}
