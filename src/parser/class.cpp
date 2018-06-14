#include "class.hpp"

#include "interpreter.hpp"
#include "environment.hpp"
#include "class_instance.hpp"

Class::Class(const std::string& name)
        : m_name(name)
{}

Value Class::call(Interpreter* inter, const std::vector<Value>& args)
{
        return new Class_Instance(this);
}

int Class::arity()
{
        return 0;
}

std::string Class::toString()
{
        return m_name;
}
