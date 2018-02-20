#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>

#include "visitor_interface.hpp"

#include "value.hpp"
#include "token.hpp"

class Stmt;
class Environment;

class Interpreter : public ExprVisitor, public StmtVisitor
{
public:
        Interpreter();

        void Interpret(std::vector<Stmt*>);

        std::string interpreter(Expr*);

        virtual void visitBinary(Binary*);
        virtual void visitLiteral(Literal*);
	virtual void visitGrouping(Grouping*);
	virtual void visitUnary(Unary*);
        virtual void visitVariableExpr(VariableExpr*);
        virtual void visitAssignExpr(AssignExpr*);
        virtual void visitLogicalExpr(LogicalExpr*);

        void execute(Stmt*);

        virtual void visitExpressionStmt(ExpressionStmt*);
        virtual void visitPrintStmt(PrintStmt*);
        virtual void visitVarStmt(VarStmt*);
        virtual void visitBlockStmt(BlockStmt*);
        virtual void visitIfStmt(IfStmt*);
        virtual void visitWhileStmt(WhileStmt*);

private:

        void executeBlock(std::vector<Stmt*>, Environment*);
private:

        Environment* m_environment;

        void checkOperands(Token,Value&,Value&);

        Value evaluate(Expr*);

        Value m_value;

        bool m_exception_happend;
};

#endif
