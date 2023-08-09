/**
 * The differnet value types. More to be added.
 */
export type ValueType = "null" | "number" | "boolean" | "string" | "object";

/**
 * Main runtime value interface to be extended upon
 */
export interface RuntimeValue {
  type: ValueType;
}

/**
 * Null runtime value
 */
export interface NullValue extends RuntimeValue {
  type: "null";
  value: "null";
}

/**
 * Number runtime value
 */
export interface NumberValue extends RuntimeValue {
  type: "number";
  value: number;
}

/**
 * Boolean runtime value
 */
export interface BooleanValue extends RuntimeValue {
  type: "boolean";
  value: boolean;
}

/**
 * String runtime value
 */
export interface StringValue extends RuntimeValue {
  type: "string";
  value: string;
}

/**
 * Object runtime value
 */
export interface ObjectValue extends RuntimeValue {
  type: "object";
  properties: { [key: string]: RuntimeValue };
}

/**
 * Make a string value
 * @param value The value
 * @return RuntimeValue
 */
export const STRING = (value: string): StringValue => {
  return { type: "string", value: value } as StringValue;
};

/**
 * Make a number value
 * @param value The value
 * @return RuntimeValue
 */
export const NUMBER = (value: number): NumberValue => {
  return { type: "number", value: value } as NumberValue;
};

/**
 * Make a null value
 * @return RuntimeValue
 */
export const NULL: NullValue = {
  type: "null",
  value: "null",
} as NullValue;

/**
 * Make a boolean value
 * @param value The boolean value
 * @return RuntimeValue
 */
export const BOOL = (value: boolean): BooleanValue => {
  return { type: "boolean", value: value } as BooleanValue;
};
