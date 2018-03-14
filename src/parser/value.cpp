#include "value.hpp"

#include "callable.hpp"

Value::Value() : m_type(_NIL)
{}

Value::Value (bool b) : m_type(BOOL),
        m_boolValue(b)
{}

Value::Value(std::string s) : m_type(_STRING),
        m_stringValue(s)
{}

Value::Value(double d) : m_type(_NUMBER),
        m_numberValue(d)
{}

Value::Value(Callable* c)
        : m_type(CALLABLE),
        m_callableValue(c)
{}

Value::Value(const Value& v)
{
        switch (v.get_type()) {
        case BOOL : m_boolValue = v.get_bool();
        case _STRING : m_stringValue = v.get_string();
        case _NUMBER : m_numberValue = v.get_number();
        case CALLABLE: m_callableValue = v.get_callable();
        }
        m_type = v.get_type();
}

Type Value::get_type() const
{
        return m_type;
}

bool Value::get_bool() const
{
        return m_boolValue;
}

std::string Value::get_string() const
{
        return m_stringValue;
}

double Value::get_number() const
{
        return m_numberValue;
}

Callable* Value::get_callable() const
{
        return m_callableValue;
}

bool Value::is_truthy()
{
        if (is_nil()) return false;
        if (is_bool()) return get_bool();
        return true;
}

bool Value::is_equal(const Value& a, const Value& b)
{
        if (a.get_type() != b.get_type()) return false;

        switch (a.get_type()) {
        case _NIL :
                return true;
        case BOOL :
                return a.get_bool() == b.get_bool();
        case _STRING :
                return a.get_string() == b.get_string();
        case _NUMBER :
                return a.get_number() == b.get_number();
        case CALLABLE:
                return false;
        }
}

bool Value::is_nil()
{
        return m_type == _NIL;
}

bool Value::is_string()
{
        return m_type == _STRING;
}

bool Value::is_number()
{
        return m_type == _NUMBER;
}

bool Value::is_bool()
{
        return m_type == BOOL;
}

bool Value::is_callable()
{
        return m_type == CALLABLE;
}

std::string Value::Stringfy()
{
        switch (m_type) {
                case _NIL :
                        return "null";
                case BOOL :
                        return m_boolValue ? "true" : "false";
                case _STRING:
                        return m_stringValue;
                case _NUMBER:
                        return std::to_string(m_numberValue);
                case CALLABLE:
                        return "callable";
        }
        return "";
}
