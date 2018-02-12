#ifndef STMT_HPP
#define STMT_HPP

#include "token.hpp"

#include <vector>

class Expr;
class StmtVisitor;

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

        IfStmt(Expr* c, Stmt* b, Stmt* e) : m_condition(c),
                m_then_branch(b),
                m_else_branch(e) {}

        virtual void accept(StmtVisitor*);

private:
        Expr* m_condition;
        Stmt* m_then_branch;
        Stmt* m_else_branch;
};
#endif
