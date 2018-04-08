#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "value.hpp"
#include "token.hpp"


#include <map>

class Environment
{
public:
        Environment();

        Environment(Environment*);

        void define(std::string, Value);

        Value get_variable(std::string);

        void assign(Token, Value);
private:

        Environment* enclosing;

        std::map<std::string, Value> m_variables;
};

#endif
