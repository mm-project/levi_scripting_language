#include "expr.hpp"
#include "interpreter.hpp"

#include <iostream>

void Binary::accept(ExprVisitor* v)
{
	v->visitBinary(this);
}

void Literal::accept(ExprVisitor* v)
{
	v->visitLiteral(this);
}

void Unary::accept(ExprVisitor* v)
{
	v->visitUnary(this);
}

void Grouping::accept(ExprVisitor* v)
{
	v->visitGrouping(this);
}

void VariableExpr::accept(ExprVisitor* v)
{
        v->visitVariableExpr(this);
}

void AssignExpr::accept(ExprVisitor* v)
{
        v->visitAssignExpr(this);
}

void LogicalExpr::accept(ExprVisitor* v)
{
        v->visitLogicalExpr(this);
}

void CallExpr::accept(ExprVisitor* v)
{
        v->visitCallExpr(this);
}

void FunctionExpr::accept(ExprVisitor* v)
{
        v->visitFunctionExpr(this);
}
