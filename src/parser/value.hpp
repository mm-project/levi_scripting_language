#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>

class Callable;
class Class_Instance;

enum Type {_NIL, _BOOL, _STRING, _NUMBER, _CALLABLE, _INSTANCE};

class Value
{
public:
        /// @brief Contructors.
        Value();
        Value(bool);
        Value(std::string);
        Value(double);
        Value(Callable*);
        Value(Class_Instance*);
        Value(const Value&);

public:
        /// @brief Gets type of the value
        Type get_type() const;

        /// @brief Gets value
        bool get_bool() const;
        std::string get_string() const;
        double get_number() const;
        Callable* get_callable() const;
        Class_Instance* get_instance() const;

        bool is_truthy();

        static bool is_equal(const Value&, const Value&);

        bool is_nil();
        bool is_string();
        bool is_number();
        bool is_bool();
        bool is_callable();
        bool is_instance();

        /// @brief Gets string value from value (for print)
        std::string Stringfy();
private:
        Type m_type;
        bool m_boolValue;
        std::string m_stringValue;
        double m_numberValue;
        Callable* m_callableValue;
        Class_Instance* m_instanceValue;
};

#endif
