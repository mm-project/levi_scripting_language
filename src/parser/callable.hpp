#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include "value.hpp"

#include <vector>

class Interpreter;

/// @class Callable
class Callable
{
public:
        /// @brief Calls the funtion
        /// @param [in] inter The Interpreter
        /// @param [in] args The arguments of the funtion
        virtual Value call(Interpreter* inter, const std::vector<Value>& args) = 0;

        /// @brief Retruns parameters size
        virtual int arity() = 0;

        /// @brief Gets the funtion name
        virtual std::string toString() = 0;
};

#endif
