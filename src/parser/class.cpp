#include "class.hpp"

#include "interpreter.hpp"
#include "environment.hpp"
#include "class_instance.hpp"
#include "function.hpp"

Class::Class(const std::string& name, const std::map<std::string, Function*>& methods)
        : m_name(name), m_methods(methods)
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

Function* Class::find_method(Class_Instance* instance, const std::string& name)
{
        auto it = m_methods.find(name);
        return (it != m_methods.end()) ? it->second : 0;
}
