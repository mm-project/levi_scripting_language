#ifndef CLASS_INSTANCE_HPP
#define CLASS_INSTANCE_HPP

#include "token.hpp"
#include "value.hpp"

#include <map>

class Class;

/// @class Class_Instance
class Class_Instance
{
public:
        /// @brief Constructor
        Class_Instance(Class*);

public:
        /// @brief Gets Class name.
        std::string toString() const;

        /// @brief Gets the value of the property
        Value get(Token);

        /// @brief Sets value of the property
        void set(Token, const Value&);
private:
        Class* m_class;
        std::map<std::string, Value> m_fields;
};
#endif
