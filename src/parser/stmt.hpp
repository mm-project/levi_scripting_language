#ifndef STMT_HPP
#define STMT_HPP

#include "token.hpp"

#include <vector>

class Expr;
class StmtVisitor;
class FunctionExpr;

class Stmt
{
public:
        virtual void accept(StmtVisitor*) = 0;
};

class PrintStmt : public Stmt
{
public:
	friend class Interpreter;

        PrintStmt(Expr* e) : m_expression(e) {}

        virtual void accept(StmtVisitor*);

private:
        Expr* m_expression;
};

class ExpressionStmt : public Stmt
{
public:
	friend class Interpreter;

        ExpressionStmt(Expr* e) : m_expression(e) {}

        virtual void accept(StmtVisitor*);

private:
        Expr* m_expression;
};

class VarStmt : public Stmt
{
public:
        friend class Interpreter;

        VarStmt(Token name, Expr* e) : m_name(name), m_expression(e) {}

        virtual void accept(StmtVisitor*);

private:
        Token m_name;
        Expr* m_expression;
};

class BlockStmt : public Stmt
{
public:
        friend class Interpreter;

        BlockStmt(std::vector<Stmt*> s) : m_stmts(s) {}

        virtual void accept(StmtVisitor*);

private:
        std::vector<Stmt*> m_stmts;
};

class IfStmt : public Stmt
{
public:
        friend class Interpreter;

        IfStmt(Expr* c, Stmt* b, Stmt* e)
                : m_condition(c),
                m_then_branch(b),
                m_else_branch(e) {}

        virtual void accept(StmtVisitor*);

private:
        Expr* m_condition;
        Stmt* m_then_branch;
        Stmt* m_else_branch;
};

class WhileStmt : public Stmt
{
public:
        friend class Interpreter;

        WhileStmt(Expr* c, Stmt* b)
                : m_condition(c),
                m_body(b) {}

        virtual void accept(StmtVisitor*);

private:
        Expr* m_condition;
        Stmt* m_body;
};

class FunctionStmt : public Stmt
{
public:
        friend class Interpreter;

        FunctionStmt(Token name, FunctionExpr* declaration)
                        : m_name(name),
                        m_declaration(declaration) {}

        virtual void accept(StmtVisitor*);

private:
        Token m_name;
        FunctionExpr* m_declaration;
};

class ReturnStmt : public Stmt
{
public:
        friend class Interpreter;

        ReturnStmt(Token k, Expr* e)
                : m_keyword(k),
                m_value(e) {}

        virtual void accept(StmtVisitor*);
private:
        Token m_keyword;
        Expr* m_value;
};

class ClassStmt : public Stmt
{
public:
        friend class Interpreter;

        ClassStmt(Token name, const std::vector<FunctionStmt*>& methods)
                : m_name(name), m_methods(methods)
        {}

        virtual void accept(StmtVisitor*);

private:
        Token m_name;
        std::vector<FunctionStmt*> m_methods;
};
#endif
