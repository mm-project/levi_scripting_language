#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>

#include "visitor_interface.hpp"

#include "value.hpp"
#include "token.hpp"

class Stmt;
class Environment;

/// @class Interpreter
class Interpreter : public ExprVisitor, public StmtVisitor
{
public:
        Interpreter();

        void Interpret(std::vector<Stmt*>);

        std::string interpreter(Expr*);

        virtual void visitBinary(Binary*) override;
        virtual void visitLiteral(Literal*) override;
	virtual void visitGrouping(Grouping*) override;
	virtual void visitUnary(Unary*) override;
        virtual void visitVariableExpr(VariableExpr*) override;
        virtual void visitAssignExpr(AssignExpr*) override;
        virtual void visitLogicalExpr(LogicalExpr*) override;
        virtual void visitCallExpr(CallExpr*) override;
        virtual void visitFunctionExpr(FunctionExpr*) override;
        virtual void visitGetExpr(GetExpr*) override;
        virtual void visitSetExpr(SetExpr*) override;

        void execute(Stmt*);

        virtual void visitExpressionStmt(ExpressionStmt*) override;
        virtual void visitPrintStmt(PrintStmt*) override;
        virtual void visitVarStmt(VarStmt*) override;
        virtual void visitBlockStmt(BlockStmt*) override;
        virtual void visitIfStmt(IfStmt*) override;
        virtual void visitWhileStmt(WhileStmt*) override;
        virtual void visitFunctionStmt(FunctionStmt*) override;
        virtual void visitReturnStmt(ReturnStmt*) override;
        virtual void visitClassStmt(ClassStmt*) override;

        void executeBlock(std::vector<Stmt*>, Environment*);
private:

        Environment* m_globals;
        Environment* m_environment;

        void checkOperands(Token,Value&,Value&);

        Value evaluate(Expr*);

        Value m_value;

        bool m_exception_happend;
};

#endif
