#ifndef EXPR_HPP
#define EXPR_HPP

#include "token.hpp"
#include "value.hpp"
#include "visitor_interface.hpp"

#include <string>
#include <vector>

#include <iostream>

class Stmt;

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

class LogicalExpr : public Expr
{
public:
        friend class Interpreter;

        LogicalExpr(Expr* left, Token op, Expr* right)
                : m_left(left), m_operator(op), m_right(right) {}

        virtual void accept(ExprVisitor*);

private:
        Expr* m_left;
        Token m_operator;
        Expr* m_right;
};

class CallExpr : public Expr
{
public:
        friend class Interpreter;

        CallExpr(Expr* callee, Token paren, std::vector<Expr*> args)
                : m_callee(callee), m_paren(paren), m_arguments(args) {}

        virtual void accept(ExprVisitor*);

private:
        Expr* m_callee = nullptr;
        Token m_paren;
        std::vector<Expr*> m_arguments;
};

class FunctionExpr : public Expr
{
public:
        friend class Interpreter;
        friend class Function;

        FunctionExpr(std::vector<Token> t, std::vector<Stmt*> s)
                : m_parameters(t), m_body(s) {}

        virtual void accept(ExprVisitor*);

        size_t parameters_size() const { return m_parameters.size();}
private:
        std::vector<Token> m_parameters;
        std::vector<Stmt*> m_body;
};

class GetExpr : public Expr
{
public:
        friend class Interpreter;
        friend class Parser;

        GetExpr(Expr* expr, Token name)
                : m_expr(expr), m_name(name)
        {}

        virtual void accept(ExprVisitor*);

private:
        Expr* m_expr;
        Token m_name;
};

class SetExpr : public Expr
{
public:
        friend class Interpreter;

        SetExpr(Expr* object, Token name, Expr* expr)
                : m_object(object), m_name(name), m_value(expr)
        {}

        virtual void accept(ExprVisitor*);

private:
        Expr* m_object;
        Token m_name;
        Expr* m_value;
};
#endif
