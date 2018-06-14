#include "class_instance.hpp"

#include "class.hpp"
#include "error.hpp"

Class_Instance::Class_Instance(Class* klass)
        : m_class(klass)
{}

std::string Class_Instance::toString() const
{
        return m_class->toString() + " instance";
}

Value Class_Instance::get(Token token)
{
        auto i = m_fields.find(token.lexeme);
        if (i != m_fields.end()) {
                return i->second;
        }
        throw Parser_error(token, "- undefined property.");
}

void Class_Instance::set(Token token, const Value& value)
{
        m_fields[token.lexeme] = value;
}
