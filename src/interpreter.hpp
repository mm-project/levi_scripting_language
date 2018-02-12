#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>

#include "visitor_interface.hpp"

#include "value.hpp"
#include "token.hpp"

class Expr;
class Binary;
class Literal;
class Unary;
class Grouping;
class Stmt;

class Environment;

class Interpreter : public ExprVisitor, public StmtVisitor
{
public:
        Interpreter();

        void Interpret(std::vector<Stmt*>);

        std::string interpreter(Expr*);

        void visitBinary(Binary*);
        void visitLiteral(Literal*);
	void visitGrouping(Grouping*);
	void visitUnary(Unary*);
        Value visitVariableExpr(VariableExpr*);
        Value visitAssignExpr(AssignExpr*);

        void execute(Stmt*);

        void visitExpressionStmt(ExpressionStmt*);
        void visitPrintStmt(PrintStmt*);
        void visitVarStmt(VarStmt*);
        void visitBlockStmt(BlockStmt*);
        void visitIfStmt(IfStmt*);

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
