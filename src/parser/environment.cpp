#include "environment.hpp"

#include "error.hpp"
#include "commands.hpp"

#include <iostream>

Environment::Environment() :enclosing(0)
{}

Environment::Environment(Environment* e) : enclosing(e)
{}

void Environment::define(const std::string& name, Value value)
{
        m_variables[name] = value;
}

Value Environment::get_variable(const std::string& name)
{
        // lookup registerd commands
        CommandPool& commands = CommandPool::getInstance();
        auto cm = commands.findCommand(name);
        if (cm != nullptr)
            return cm;

        auto search = m_variables.find(name);
        if (search != m_variables.end()) {
                return search->second;
        }
        if (enclosing) {
                return enclosing->get_variable(name);
        }
        throw Runtime_error("Undefined variable " + name + ".");
}

void Environment::assign(const std::string& name, Value value)
{
        auto search = m_variables.find(name);
        if (search != m_variables.end()) {
                m_variables[name] = value;
                return;
        }
        if (enclosing) {
                enclosing->assign(name, value);
                return;
        }
        throw Runtime_error("Undefined reference " + name + ".");
}

