#ifndef NATIVE_FUNCTIONS_HPP
#define NATIVE_FUNCTIONS_HPP

#include "callable.hpp"

class ClockFunction : public Callable
{
public:
        virtual Value call(Interpreter* , const std::vector<Value>&) {
                //return Value(std::string(clock() * 1000 / CLOCKS_PER_SEC)); //current time
                return Value();
        }

        virtual int arity() {
                return 0;
        }

        virtual std::string toString() {
                return "native funciton";
        }
};

#endif
