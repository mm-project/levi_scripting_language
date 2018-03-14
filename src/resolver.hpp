#ifndef RESOLVER_HPP
#define RESOLVER_HPP

#include "visitor_interface.hpp"

class Interpreter;

class Resolver : public ExprVisitor,
                 public StmtVisitor
{
public:
        Resolver(Interpreter* i) : interpreter(i) {}

private:
        Interpreter* interpreter;
};

#endif
