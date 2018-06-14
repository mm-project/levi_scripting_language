#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "callable.hpp"

class FunctionExpr;
class Environment;

/// @brief class Funtion
class Function : public Callable
{
public:
        /// @brief Constructor
        /// param [in] declaration The function declaration
        /// param [in] environ The function environment
        /// param [in] name The funtion name
        Function(FunctionExpr* declaration, Environment* eviron, bool, std::string name = "");

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
        FunctionExpr* m_declaration;
        Environment* m_environment;
        bool m_is_init;
        std::string m_name;
};

#endif
