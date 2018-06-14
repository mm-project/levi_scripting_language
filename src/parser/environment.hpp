#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "value.hpp"
#include "token.hpp"


#include <map>

/// @class Environment
class Environment
{
public:
        /// @brief Constructors.
        Environment();
        Environment(Environment*);

public:
        /// @brief Defines variable
        /// @param [in] name The name of the variable
        /// @param [in] value The value of the variable
        void define(const std::string& name, Value value);

        /// @brief Gets variable value
        /// @param [in] name The varibale name
        /// @return Value of the Variable
        Value get_variable(const std::string& name);

        /// @brief Assign variable to the value
        /// @param name The name of the variable
        /// @param value The value of the variable
        void assign(const std::string& name, Value value);

private:

        Environment* enclosing;
        std::map<std::string, Value> m_variables;
};

#endif
