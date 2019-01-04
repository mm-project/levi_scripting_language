#ifndef CLASS_HPP
#define CLASS_HPP

#include "callable.hpp"

#include <map>

class Class_Instance;
class Function;

/// @class Class
class Class : public Callable
{
public:
        /// @brief Constructor
        /// @param name The name
        /// @param methods The methods
        Class(const std::string& name, const std::map<std::string, Function*>& methods);
public:
        /// @brief Calls the funtion
        /// @param [in] inter The Interpreter
        /// @param [in] args The arguments of the funtion
        virtual Value call(Interpreter* inter, const std::vector<Value>& args);

        /// @brief Retruns parameters size
        virtual int arity();

        /// @brief Gets the funtion name
        virtual std::string toString();

        /// @brief Finds the method with the given name
        /// @param instance The instance
        /// @param name The method name
        Function* find_method(Class_Instance* instance, const std::string& name);
private:
        std::string m_name;
        std::map<std::string, Function*> m_methods;
};

#endif
