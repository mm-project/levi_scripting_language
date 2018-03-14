#include "function.hpp"

#include "error.hpp"
#include "interpreter.hpp"
#include "return.hpp"

#include <iostream>

Function::Function(FunctionExpr* decl, Environment* env, bool init, std::string s)
        : m_declaration(decl),
        m_environment(env),
        m_is_init(init),
        m_name(s)
{}

int Function::arity()
{
        return m_declaration->m_parameters.size();
}

std::string Function::toString()
{
        return "<fn " + m_name + ">";
}

Value Function::call(Interpreter* inter, std::vector<Value> args)
{
        Environment* env = new Environment(m_environment);

        for (unsigned i = 0; i < args.size(); ++i) {
                std::string name = m_declaration->m_parameters[i].lexeme;
                env->define(name, args[i]);
        }

        try {
                inter->executeBlock(m_declaration->m_body, env);
        } catch (Return& e) {
                return e.m_value;
        }
        return Value();
}

