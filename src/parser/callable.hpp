#ifndef CALLABLE_HPP
#define CALLABLE_HPP

#include "value.hpp"

#include <vector>

class Interpreter;

class Callable
{
public:
        virtual Value call(Interpreter* inter, std::vector<Value> args) = 0;

        virtual int arity() = 0;

        virtual std::string toString() = 0;
};

#endif
