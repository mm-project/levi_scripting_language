#ifndef EXPR_HPP
#define EXPR_HPP

#include "token.hpp"
#include "value.hpp"
#include "visitor_interface.hpp"

#include <string>

class Expr {
public:
	virtual void accept(ExprVisitor*) = 0;
};

class Binary : public Expr {
public:
	friend class Interpreter;
	Binary(Expr* l, Token o, Expr* r) : m_left(l), m_operator(o), m_right(r) {}

	virtual void accept(ExprVisitor*);

private:
	Expr* m_left;
	Token m_operator;
	Expr* m_right;
};

class Literal : public Expr {
public:
	friend class Interpreter;
	Literal(Value l): m_literal(l) {}

	virtual void accept(ExprVisitor*);

private:
	Value m_literal;
};

class Grouping : public Expr {
public:
	friend class Interpreter;
	Grouping(Expr* g): m_grouping(g) {}

	virtual void accept(ExprVisitor*);

private :
	Expr* m_grouping;
};

class Unary : public Expr {
public:
	friend class Interpreter;
	Unary(Token o, Expr* r): m_operator(o), m_right(r)  {}

	virtual void accept(ExprVisitor*);

private:
	Token m_operator;
	Expr* m_right;
};

class VariableExpr : public Expr
{
public:
        friend class Interpreter;

        VariableExpr(Token name) : m_name(name) {}

        virtual void accept(ExprVisitor*);

        Token get_name() const {return m_name;}
private:
        Token m_name;
};

class AssignExpr : public Expr
{
public:
        friend class Interpreter;

        AssignExpr(Token name, Expr* value) : m_name(name), m_value(value) {}

        virtual void accept(ExprVisitor*);

private:
        Token m_name;
        Expr* m_value;
};

#endif
