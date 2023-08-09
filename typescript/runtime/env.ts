import { RuntimeValue, BOOL } from "./values.ts";

export default class Environment {
  private parent: Environment | null;
  private values: {
    [key: string]: { value: RuntimeValue; constant: boolean };
  } = {};

  constructor(parent: Environment | null = null) {
    this.parent = parent;
    this.setPrimitiveVariables();
  }

  /**
   * Set the initial variables such as boolean, null booleans, etc.
   * @returns void
   */
  public setPrimitiveVariables(): void {
    this.declare("true", BOOL(true), true);
    this.declare("false", BOOL(false), true);
    this.declare("null", BOOL(false), true);
  }

  /**
   * Declare a variable
   * @param name The variable name
   * @param value The variable's value
   * @returns The variable value
   */
  public declare(
    name: string,
    value: RuntimeValue,
    constant: boolean
  ): RuntimeValue {
    if (this.values[name] !== undefined) {
      throw new Error(`Variable already declared: ${name}`);
    }
    this.values[name] = {
      value: value,
      constant: constant,
    };
    return value;
  }

  /**
   * Resolve an environment
   * @param name The name of the variable
   * @returns The variable value
   */
  public resolve(name: string): Environment {
    if (this.values[name] === undefined) {
      if (this.parent === null) {
        throw new Error(`Undefined variable: ${name}`);
      }
      return this.parent.resolve(name);
    }
    return this;
  }

  /**
   * Reassign a variable in the environment
   * @param name The variable name
   * @param value The variable value
   * @returns The provided value
   */
  public assign(name: string, value: RuntimeValue): RuntimeValue {
    // Resolve the environment
    const env: Environment = this.resolve(name);

    // Check if the variable is constant
    if (env.values[name].constant) {
      throw new Error(`Cannot reassign constant variable: ${name}`);
    }

    // Assign the variable
    env.values[name] = {
      value: value,
      constant: false,
    };

    // Return the value
    return value;
  }

  /**
   * Get a variable
   *
   * @param name The variable name
   * @returns The variable value
   */
  public get(name: string): RuntimeValue {
    const env: Environment = this.resolve(name);
    return env.values[name].value;
  }

  /**
   * Get whether a value is constant
   * @param name The variable name
   * @returns Whether the value is constant
   */
  public isConstant(name: string): boolean {
    const env: Environment = this.resolve(name);
    return env.values[name].constant;
  }
}
