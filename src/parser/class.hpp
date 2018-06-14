#ifndef CLASS_HPP
#define CLASS_HPP

#include "callable.hpp"

/// @class Class
class Class : public Callable
{
public:
        /// @brief Constructor
        Class(const std::string& name);
public:
        /// @brief Calls the funtion
        /// @param [in] inter The Interpreter
        /// @param [in] args The arguments of the funtion
        virtual Value call(Interpreter* inter, const std::vector<Value>& args);

        /// @brief Retruns parameters size
        virtual int arity();

        /// @brief Gets the funtion name
        virtual std::string toString();

private:
        std::string m_name;
};

#endif
