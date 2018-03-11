#include "environment.hpp"

#include "error.hpp"

#include <iostream>

Environment::Environment() :enclosing(0)
{}

Environment::Environment(Environment* e) : enclosing(e)
{}

void Environment::define(std::string name, Value var)
{
        m_variables[name] = var;
}

Value Environment::get_variable(std::string name)
{
        auto search = m_variables.find(name);
        if (search != m_variables.end()) {
                return search->second;
        }
        if (enclosing) {
                return enclosing->get_variable(name);
        }
        throw Runtime_error("Undefined variable " + name + ".");
}

void Environment::assign(Token name, Value v)
{
        std::string n = name.lexeme;
        auto search = m_variables.find(n);
        if (search != m_variables.end()) {
                m_variables[n] = v;
                return;
        }
        if (enclosing) {
                enclosing->assign(name, v);
                return;
        }
        throw Runtime_error("Undefined reference " + n + ".");
}

