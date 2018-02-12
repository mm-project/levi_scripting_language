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

class ExpressionStmt;
class PrintStmt;
class VarStmt;
class BlockStmt;
class IfStmt;

class ExprVisitor
{
public:
        virtual void visitBinary(Binary*) = 0;
        virtual void visitUnary(Unary*) = 0;
        virtual void visitGrouping(Grouping*) = 0;
        virtual void visitLiteral(Literal*) = 0;
        virtual Value visitVariableExpr(VariableExpr*) = 0;
        virtual Value visitAssignExpr(AssignExpr*) = 0;
};

class StmtVisitor
{
public:
        virtual void visitExpressionStmt(ExpressionStmt*) = 0;
        virtual void visitPrintStmt(PrintStmt*) = 0;
        virtual void visitVarStmt(VarStmt*) = 0;
        virtual void visitBlockStmt(BlockStmt*) = 0;
        virtual void visitIfStmt(IfStmt*) = 0;
};

#endif
