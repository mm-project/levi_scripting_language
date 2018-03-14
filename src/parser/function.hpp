#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "callable.hpp"

#include "expr.hpp"
#include "environment.hpp"

class Function : public Callable
{
public:
        Function(FunctionExpr*, Environment*, bool, std::string = "");

        virtual Value call(Interpreter* inter, std::vector<Value> args);

        virtual int arity();

        virtual std::string toString();

private:
        FunctionExpr* m_declaration;
        Environment* m_environment;
        bool m_is_init;
        std::string m_name;
};

#endif
