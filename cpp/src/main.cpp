#ifndef MAIN
#define MAIN

#include <iostream>
#include "parser.hpp"
#include "runtime/interpreter.hpp"
#include "runtime/env.hpp"

int main()
{
    // Create a new environment with no parent env
    Environment *env = new Environment(nullptr);

    // Create a new parser
    Parser *parser = new Parser();

    // Create a new interpreter
    Interpreter *interpreter = new Interpreter();

    std::string input = "";
    while (input != "exit")
    {
        std::cout << ">> ";
        std::getline(std::cin, input);

        // Parse the input
        Program *program = parser->parse(input);

        // Get the result
        RuntimeValue *result = interpreter->evaluate(program, env);

        // Print the result
        std::cout << runtime_value_to_string(result) << std::endl;
    }

    return 0;
}

#endif // MAIN