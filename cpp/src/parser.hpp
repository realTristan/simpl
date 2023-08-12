#ifndef PARSER_HPP
#define PARSER_HPP

#include "./lexer.hpp"
#include "./ast.hpp"

#include <vector>
#include <string>

class Parser
{
private:
  std::vector<Token *> tokens;

  /**
   * Shift the tokens
   */
  Token *shift_tokens()
  {
    // Get the first character
    Token *t = this->tokens[0];

    // Remove the first character
    this->tokens.erase(this->tokens.begin());

    // Return the first character
    return t;
  }

  /**
   * Expect a token type. If it doesn't equal the type,
   * throw an error.
   * @param token the token
   * @param type the token type to expect
   * @param error the error to throw
   * @return bool
   */
  bool expect_token(Token *token, TokenType type, std::string error)
  {
    if (token && token->type != type)
    {
      throw std::runtime_error(error);
    }
    return true;
  }

  /**
   * Expect an expression type. If it doesn't equal the type,
   * throw an error.
   * @param expr the expression
   * @param type the node type to expect
   * @param error the error to throw
   * @return bool
   */
  bool expect_expr(Expr *expr, NodeType type, std::string error)
  {
    if (expr && expr->type != type)
      ;
    {
      throw std::runtime_error(error);
    }
    return true;
  }

  /**
   * Get the current token
   * @return Token
   */
  Token *current_token()
  {
    return this->tokens[0];
  }

  /**
   * If the current token is a semicolon, remove it.
   * @return void
   */
  void shift_semicolon()
  {
    const Token *_current_token = this->current_token();
    if (_current_token && _current_token->type == TokenType::Semicolon)
    {
      this->shift_tokens();
    }
  }

  /**
   * Check if the current token is an additive
   * @return bool
   */
  bool current_token_additive()
  {
    const Token *_current_token = this->current_token();
    return (
        _current_token->type == TokenType::BinaryOperator &&
        (_current_token->value == "+" || _current_token->value == "-"));
  }

  /**
   * Check if the current token is a multiplicative
   * @return bool
   */
  bool current_token_multiplicative()
  {
    const Token *_current_token = this->current_token();
    return (
        _current_token->type == TokenType::BinaryOperator && (_current_token->value == "*" ||
                                                              _current_token->value == "/" ||
                                                              _current_token->value == "%"));
  }

public:
  /**
   * Parse the source code
   * @param src the source code
   * @return the program
   */
  Program *parse(std::string src)
  {
    // Tokenize the source code
    this->tokens = Tokenizer::tokenize(src);

    // Create a new program
    Program *program = new Program();
    program->body = std::vector<Stmt *>();

    while (this->tokens.size() > 0)
    {
      Stmt *stmt = this->parseStmt();
      program->body.push_back(stmt);
    }

    // Return the program
    return program;
  }

  /**
   * Parse a statement
   * @return Stmt
   */
  Stmt *parseStmt()
  {
    switch (this->current_token()->type)
    {
    case TokenType::Let:
    case TokenType::Const:
    {
      Stmt *stmt = this->parseVarDeclaration();
      this->shift_semicolon();
      return stmt;
    }

    case TokenType::Function:
    {
      Stmt *stmt = this->parseFnDeclaration();
      this->shift_semicolon();
      return stmt;
    }

    default:
    {
      Expr *stmt = this->parseExpr();
      this->shift_semicolon();
      return stmt;
    }
    }
  }

  /**
   * Parse a variable declaration
   * @return Stmt
   */
  Stmt *parseVarDeclaration()
  {
    // Get whether an immutable assignment
    bool is_const = this->shift_tokens()->type == TokenType::Const;

    // Get the variable name (Identifier)
    Token *identifier = this->shift_tokens();
    this->expect_token(identifier, TokenType::Identifier, "Expected identifier");

    // Get the next value after the indentifier. This can either be a semicolon
    // Example: const var;
    // Or if the next is an equals: const var = value;
    Token *next = this->shift_tokens();

    // If the next token is a semi colon, then we are done
    if (next && next->type == TokenType::Semicolon)
    {
      VariableDeclaration *var_declaration = new VariableDeclaration();
      var_declaration->type = NodeType::VARIABLE_DECLARATION;
      var_declaration->identifier = identifier->value;
      var_declaration->constant = is_const;
      return var_declaration;
    }

    // Make sure the next token is an equals for variable assignment.
    if (next->type != TokenType::Equals)
    {
      throw std::runtime_error("Expected variable assignment");
    }

    // Get the declaration
    Expr *value = this->parseExpr();

    // Return the declaration
    VariableDeclaration *var_declaration = new VariableDeclaration();
    var_declaration->type = NodeType::VARIABLE_DECLARATION;
    var_declaration->identifier = identifier->value;
    var_declaration->constant = is_const;
    var_declaration->value = value;
    return var_declaration;
  }

  /**
   * Parse a function declaration
   * @return Stmt
   */
  Stmt *parseFnDeclaration()
  {
    // Shift past the fn
    this->shift_tokens();

    // Get the function name
    Token *name = this->shift_tokens();
    this->expect_token(name, TokenType::Identifier, "Expected identifier");

    // Get the arguments
    std::vector<Expr *> args = this->parseArgs();
    std::vector<std::string> params;

    // Make sure the arguments are all identifiers
    for (Expr *arg : args)
    {
      if (arg->type != NodeType::IDENTIFIER)
      {
        throw std::runtime_error("Invalid function argument");
      }

      // Convert the argument to an identifier
      struct Identifier *id = (struct Identifier *)arg;
      params.push_back(id->value);
    }

    // Verify that the next token is an open brace
    Token *open_brace = this->shift_tokens();
    this->expect_token(open_brace, TokenType::OpenBrace, "Expected open brace");

    // Create an array of body statements
    std::vector<Stmt *> body;

    // While there are still tokens to parse
    while (this->tokens.size() > 0 && this->current_token()->type != TokenType::CloseBrace)
    {
      Stmt *stmt = this->parseStmt();
      body.push_back(stmt);
    }

    // Verify that the next token is a close brace
    Token *close_brace = this->shift_tokens();
    this->expect_token(close_brace, TokenType::CloseBrace, "Expected close brace");

    // Return the function declaration
    FunctionDeclaration *fn_declaration = new FunctionDeclaration();
    fn_declaration->type = NodeType::FUNCTION_DECLARATION;
    fn_declaration->name = name->value;
    fn_declaration->params = params;
    fn_declaration->body = body;
    return fn_declaration;
  }

  /**
   * Parse an expression
   * @return Expr
   */
  Expr *parseExpr()
  {
    return this->parseAssignmentExpr();
  }

  /**
   * Parse an assignment expression
   * @return Expr
   */
  Expr *parseAssignmentExpr()
  {
    // Get the left side of the expression
    Expr *left = this->parseObjectExpr();

    // Check if the current token is an equals
    if (this->current_token() && this->current_token()->type == TokenType::Equals)
    {
      // Move past the equals token
      this->shift_tokens();

      // Allow for assignment chaining
      Expr *value = this->parseAssignmentExpr();

      // If the left side is not an identifier, throw an error
      this->expect_expr(left, NodeType::IDENTIFIER, "Expected identifier");

      // Convert the left side to an identifier
      struct Identifier *assignee = new struct Identifier();
      assignee->type = NodeType::IDENTIFIER;
      assignee->value = ((struct Identifier *)left)->value;

      // Return the assignment expression
      AssignmentExpr *assignment_expr = new AssignmentExpr();
      assignment_expr->type = NodeType::ASSIGNMENT_EXPR;
      assignment_expr->assignee = assignee;
      assignment_expr->value = value;
      return assignment_expr;
    }

    // Return the left side
    return left;
  }

  /**
   * Parse an object expression
   * @return Expr
   */
  Expr *parseObjectExpr()
  {
    // If the start of an object expression
    if (this->current_token() && this->current_token()->type != TokenType::OpenBrace)
    {
      return this->parseAdditiveExpr();
    }

    // Move past the open brace
    this->shift_tokens();

    // Create an array of properties
    std::vector<Property *> properties;

    // While there are still tokens to parse
    while (
        this->tokens.size() > 0 &&
        this->current_token() &&
        this->current_token()->type != TokenType::CloseBrace)
    {
      // Get the object key
      Token *key = this->shift_tokens();
      this->expect_token(key, TokenType::Identifier, "Expected identifier");

      // Get the next token
      Token *next = this->shift_tokens();

      // If the next is a comma
      if (next && (next->type == TokenType::Comma || next->type == TokenType::CloseBrace))
      {
        // Add the property
        Property *property = new Property();
        property->type = NodeType::PROPERTY;
        property->key = key->value;
        properties.push_back(property);

        // Continue the loop
        continue;
      }

      // If the next is a colon
      this->expect_token(next, TokenType::Colon, "Expected colon");

      // Add the property
      Property *property = new Property();
      property->type = NodeType::PROPERTY;
      property->key = key->value;
      property->value = this->parseExpr();
      properties.push_back(property);

      // Get the next token
      Token *closing = this->shift_tokens();

      // If the next is a comma
      if (closing && (closing->type == TokenType::Comma || closing->type == TokenType::CloseBrace))
      {
        continue;
      }
    }

    // Make sure the end is a close brace or a comma
    Token *end = this->shift_tokens();
    if (end && end->type != TokenType::CloseBrace && end->type != TokenType::Comma)
    {
      throw std::runtime_error("Expected close brace or comma");
    }

    // Return the object expression
    ObjectLiteral *object_literal = new ObjectLiteral();
    object_literal->type = NodeType::OBJECT_LITERAL;
    object_literal->properties = properties;
    return object_literal;
  }

  /**
   * Parse an additive expression
   * @return Expr
   */
  Expr *parseAdditiveExpr()
  {
    // Get the left side of the expression
    Expr *left = this->parseMultiplicativeExpr();

    // While there are still tokens to parse
    while (this->tokens.size() > 0 && this->current_token_additive() && left)
    {
      // Get the expression operator
      Token *op = this->shift_tokens();

      // Get the right side of the expression
      Expr *right = this->parseMultiplicativeExpr();

      // Covnert left to a binary expression
      BinaryExpr *_left = (BinaryExpr *)left;

      // Create a binary expression
      BinaryExpr *binexpr = new BinaryExpr();
      binexpr->type = NodeType::BINARY_EXPR;
      binexpr->op = op->value[0];
      binexpr->left = _left;
      binexpr->right = right;

      // Set the left to the new binary expression
      left = binexpr;
    }

    // Return the left side of the expression. We do this because
    // the left side becomes the entire binary expression
    return left;
  }

  /**
   * Parse a multiplicative expression
   * @return Expr
   */
  Expr *parseMultiplicativeExpr()
  {
    // Get the left side of the expression
    Expr *left = this->parseCallMemberExpr();

    // While there are still tokens to parse
    while (this->tokens.size() > 0 && this->current_token_multiplicative() && left)
    {
      // Get the expression operator
      Token *op = this->shift_tokens();

      // Get the right side of the expression
      Expr *right = this->parseCallMemberExpr();

      // Covnert left to a binary expression
      BinaryExpr *_left = (BinaryExpr *)left;

      // Create a binary expression
      BinaryExpr *binexpr = new BinaryExpr();
      binexpr->type = NodeType::BINARY_EXPR;
      binexpr->op = op->value[0];
      binexpr->left = _left;
      binexpr->right = right;

      // Set the left to the new binary expression
      left = binexpr;
    }

    // Return the left side of the expression. We do this because
    // the left side becomes the entire binary expression
    return left;
  }

  /**
   * Parse a call member expression
   * @return Expr
   */
  Expr *parseCallMemberExpr()
  {
    Expr *member = this->parseMemberExpr();
    if (this->current_token() && this->current_token()->type == TokenType::OpenParen)
    {
      return this->parseCallExpr(member);
    }
    return member;
  }

  /**
   * Parse a call expression
   * @param caller the caller
   * @return Expr
   */
  CallExpr *parseCallExpr(Expr *caller)
  {
    // Create a call expression
    CallExpr *call_expr = new CallExpr();
    call_expr->type = NodeType::CALL_EXPR;
    call_expr->caller = caller;
    call_expr->args = this->parseArgs();

    // If open paren
    if (this->current_token() && this->current_token()->type == TokenType::OpenParen)
    {
      call_expr = this->parseCallExpr(call_expr);
    }

    // Return the call expression
    return call_expr;
  }

  /**
   * Parse arguments
   * @return Expr
   */
  std::vector<Expr *> parseArgs()
  {
    // Make sure the next token is an open paren
    Token *open_paren = this->shift_tokens();
    this->expect_token(open_paren, TokenType::OpenParen, "Expected open paren");

    // Create an array of arguments
    std::vector<Expr *> args;

    // While there are still tokens to parse
    while (
        this->tokens.size() > 0 &&
        this->current_token() &&
        this->current_token()->type != TokenType::CloseParen)
    {
      args.push_back(this->parseAssignmentExpr());

      // If the next token is a closing paren
      Token *next = this->shift_tokens();
      if (next && next->type == TokenType::CloseParen)
      {
        break;
      }
    }

    // Return the arguments
    return args;
  }

  /**
   * Parse a member expression
   * @return Expr
   */
  Expr *parseMemberExpr()
  {
    Expr *object = this->parsePrimaryExpr();

    // If the current token is a dot or open bracket
    while (
        this->current_token() &&
        (this->current_token()->type == TokenType::Dot ||
         this->current_token()->type == TokenType::OpenBracket))
    {
      // Get the operator
      Token *op = this->shift_tokens();

      // Non computed
      if (op->type == TokenType::Dot)
      {
        // Get the property
        Expr *property = this->parsePrimaryExpr();

        // Expect an identifier
        this->expect_expr(property, NodeType::IDENTIFIER, "Expected identifier");

        // Update the object
        MemberExpr *member_expr = new MemberExpr();
        member_expr->type = NodeType::MEMBER_EXPR;
        member_expr->object = object;
        member_expr->property = property;
        member_expr->computed = false;
        object = member_expr;
      }

      // Computed
      else
      {
        // Get the closing bracket
        Token *bracket = this->shift_tokens();
        this->expect_token(bracket, TokenType::CloseBracket, "Expected close bracket");

        // Update the object
        MemberExpr *member_expr = new MemberExpr();
        member_expr->type = NodeType::MEMBER_EXPR;
        member_expr->object = object;
        member_expr->property = this->parseExpr();
        member_expr->computed = true;
        object = member_expr;
      }
    }

    // Return the object
    return object;
  }

  /**
   * Parse a binary expression parenthesis
   * @return Expr
   */
  Expr *parseBinaryExprParen()
  {
    // Parse the expression without the open paren
    Expr *expr = this->parseExpr();

    // Get the close paren and make sure it's valid. If it's
    // not, throw an error.
    Token *close_paren = this->shift_tokens();
    this->expect_token(close_paren, TokenType::CloseParen, "Expected close paren");

    // Return the expression
    return expr;
  }

  /**
   * Parse a primary expression
   * @return Expr
   */
  Expr *parsePrimaryExpr()
  {
    // Get the current token
    Token *token = this->shift_tokens();

    // Numeric Literal Expression
    if (token->type == TokenType::Number)
    {
      NumericLiteral *num = new NumericLiteral();
      num->value = std::stod(token->value);
      return num;
    }

    // Identifier Expression
    if (token->type == TokenType::Identifier)
    {
      struct Identifier *id = new struct Identifier();
      id->value = token->value;
      return id;
    }

    // Null Literal Expression
    if (token->type == TokenType::Null)
    {
      NullLiteral *null = new NullLiteral();
      null->value = nullptr;
      return null;
    }

    // Handle the open paren
    if (token->type == TokenType::OpenParen)
    {
      return this->parseBinaryExprParen();
    }

    // Error
    throw std::runtime_error("Unexpected token");
  }
};

#endif // PARSER_HPP