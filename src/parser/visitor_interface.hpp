#ifndef VISITOR_INTERFACE_HPP
#define VISITOR_INTERFACE_HPP

#include "value.hpp"

class Expr;
class Binary;
class Unary;
class Literal;
class Grouping;
class VariableExpr;
class AssignExpr;
class LogicalExpr;
class CallExpr;
class FunctionExpr;
class GetExpr;
class SetExpr;

class ExpressionStmt;
class PrintStmt;
class VarStmt;
class BlockStmt;
class IfStmt;
class WhileStmt;
class FunctionStmt;
class ReturnStmt;
class ClassStmt;

/// @class Expression Visitor
class ExprVisitor
{
public:
        virtual void visitBinary(Binary*) = 0;
        virtual void visitUnary(Unary*) = 0;
        virtual void visitGrouping(Grouping*) = 0;
        virtual void visitLiteral(Literal*) = 0;
        virtual void visitVariableExpr(VariableExpr*) = 0;
        virtual void visitAssignExpr(AssignExpr*) = 0;
        virtual void visitLogicalExpr(LogicalExpr*) = 0;
        virtual void visitCallExpr(CallExpr*) = 0;
        virtual void visitFunctionExpr(FunctionExpr*) = 0;
        virtual void visitGetExpr(GetExpr*) = 0;
        virtual void visitSetExpr(SetExpr*) = 0;
};

/// @class Statement Visitor
class StmtVisitor
{
public:
        virtual void visitExpressionStmt(ExpressionStmt*) = 0;
        virtual void visitPrintStmt(PrintStmt*) = 0;
        virtual void visitVarStmt(VarStmt*) = 0;
        virtual void visitBlockStmt(BlockStmt*) = 0;
        virtual void visitIfStmt(IfStmt*) = 0;
        virtual void visitWhileStmt(WhileStmt*) = 0;
        virtual void visitFunctionStmt(FunctionStmt*) = 0;
        virtual void visitReturnStmt(ReturnStmt*) = 0;
        virtual void visitClassStmt(ClassStmt*) = 0;
};

#endif
