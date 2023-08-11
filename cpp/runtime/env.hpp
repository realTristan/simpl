#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <map>
#include "values.hpp"

class Environment
{
private:
  Environment *parent;
  std::map<std::string, RuntimeValue *> values;

public:
  Environment(Environment *parent)
  {
    this->parent = parent;
  };

  /**
   * Declare a variable in the current environment.
   */
  RuntimeValue *declare(std::string name, RuntimeValue *value, bool constant)
  {
    if (values.find(name) != values.end())
    {
      throw std::runtime_error("Variable already declared: " + name);
    }
    values[name] = value;
    return value;
  };

  Environment *resolve(std::string name)
  {
    if (values.find(name) == values.end())
    {
      if (parent == nullptr)
      {
        throw std::runtime_error("Undefined variable: " + name);
      }
      return parent->resolve(name);
    }
    return this;
  };

  RuntimeValue *assign(std::string name, RuntimeValue *value)
  {
    Environment *env = resolve(name);
    env->values[name] = value;
    return value;
  };

  RuntimeValue *get(std::string name)
  {
    Environment *env = resolve(name);
    if (env->values.find(name) == env->values.end())
    {
      throw std::runtime_error("Undefined variable: " + name);
    }
    return env->values[name];
  };

  void setPrimitiveVariables()
  {
    declare("true", Make::BOOL_VALUE(true), true);
    declare("false", Make::BOOL_VALUE(false), true);
    declare("null", Make::NULL_VALUE(), true);
  };
};

#endif // ENVIRONMENT_HPP