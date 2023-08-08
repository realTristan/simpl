import Parser from "./parser.ts"
import { Program } from "./ast.ts"

// Source code to parse
const src: string = "x * ( 5 + 4 )"

// Create a parser
const parser: Parser = new Parser()

// Parse the source code
const program: Program = parser.parse(src)

// Print the AST
console.log(program)



// deno run main.ts