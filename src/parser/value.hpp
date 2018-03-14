#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>

class Callable;

enum Type {_NIL, BOOL, _STRING, _NUMBER, CALLABLE};

class Value
{
public:
        Value();
        Value(bool);
        Value(std::string);
        Value(double);
        Value(Callable*);
        Value(const Value&);

        Type get_type() const;
        bool get_bool() const;
        std::string get_string() const;
        double get_number() const;
        Callable* get_callable() const;

        bool is_truthy();

        static bool is_equal(const Value&, const Value&);

        bool is_nil();
        bool is_string();
        bool is_number();
        bool is_bool();
        bool is_callable();

        std::string Stringfy();
private:
        Type m_type;
        bool m_boolValue;
        std::string m_stringValue;
        double m_numberValue;
        Callable* m_callableValue;
};

#endif
