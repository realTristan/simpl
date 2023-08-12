#ifndef VALUES_HPP
#define VALUES_HPP

#include <map>
#include <string>

#include "../ast.hpp"
#include "env.hpp"

typedef enum ValueType
{
  _NULL,
  NUMBER,
  BOOLEAN,
  STRING,
  OBJECT,
  NATIVEFN,
  FN,
} ValueType;

/**
 * RuntimeValue
 */
typedef struct RuntimeValue
{
  ValueType type;
} RuntimeValue;

/**
 * Convert the runtime value to a string
 * @param value The runtime value to convert
 * @return The string representation of the runtime value
*/
std::string runtime_value_to_string(RuntimeValue *value)
{
  switch (value->type)
  {
  case ValueType::_NULL:
    return "null";
  case ValueType::OBJECT:
    return "object";
  case ValueType::NATIVEFN:
    return "nativefn";
  case ValueType::FN:
    return "fn";
  default:
    return "unknown";
  }
}

/**
 * NullValue
 */
typedef struct NullValue : RuntimeValue
{
  ValueType type = ValueType::_NULL;
} NullValue;

/**
 * NumberValue
 */
typedef struct NumberValue : RuntimeValue
{
  ValueType type = ValueType::NUMBER;
  double value;
} NumberValue;

/**
 * BooleanValue
 */
typedef struct BooleanValue : RuntimeValue
{
  ValueType type = ValueType::BOOLEAN;
  bool value;
} BooleanValue;

/**
 * StringValue
 */
typedef struct StringValue : RuntimeValue
{
  ValueType type = ValueType::STRING;
  std::string value;
} StringValue;

/**
 * ObjectValue
 */
typedef struct ObjectValue : RuntimeValue
{
  ValueType type = ValueType::OBJECT;
  std::map<std::string, RuntimeValue *> properties;
} ObjectValue;

/**
 * NativeFnValue
 */
typedef struct NativeFnValue : RuntimeValue
{
  ValueType type = ValueType::NATIVEFN;
  RuntimeValue *(*call)(std::vector<RuntimeValue *> args);
} NativeFnValue;

/**
 * FnValue
 */
/*typedef struct FnValue : RuntimeValue
{
  ValueType type = ValueType::FN;
  std::string name;
  std::vector<std::string> params;
  Environment *env;
  std::vector<Stmt *> body;
} FnValue;*/

/**
 * Make - Helper class for creating runtime values
 */
class Make
{
public:
  /**
   * Make a new null runtime value
   */
  static NullValue *NULL_VALUE()
  {
    NullValue *v = new NullValue();
    return v;
  }

  /**
   * Make a new number runtime value
   */
  static NumberValue *NUMBER_VALUE(double value)
  {
    NumberValue *v = new NumberValue();
    v->value = value;
    return v;
  }

  /**
   * Make a new boolean runtime value
   */
  static BooleanValue *BOOL_VALUE(bool value)
  {
    BooleanValue *v = new BooleanValue();
    v->value = value;
    return v;
  }

  /**
   * Make a new string runtime value
   */
  static StringValue *STRING_VALUE(std::string value)
  {
    StringValue *v = new StringValue();
    v->value = value;
    return v;
  }

  /**
   * Make a new object runtime value
   */
  static ObjectValue *OBJECT_VALUE(std::map<std::string, RuntimeValue *> properties)
  {
    ObjectValue *v = new ObjectValue();
    v->properties = properties;
    return v;
  }

  /**
   * Make a new native function runtime value
   */
  static NativeFnValue *NATIVEFN_VALUE(RuntimeValue *(*call)(std::vector<RuntimeValue *> args))
  {
    NativeFnValue *v = new NativeFnValue();
    v->call = call;
    return v;
  }

  /**
   * Make a new function runtime value
   */
  /*static FnValue *FN_VALUE(std::string name, std::vector<std::string> params, Environment *env, std::vector<Stmt *> body)
  {
    FnValue *v = new FnValue();
    v->name = name;
    v->params = params;
    v->env = env;
    v->body = body;
    return v;
  }*/
};

#endif // VALUES_HPP