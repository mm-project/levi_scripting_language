#include "stmt.hpp"

#include "visitor_interface.hpp"

void PrintStmt::accept(StmtVisitor* v)
{
        v->visitPrintStmt(this);
}

void ExpressionStmt::accept(StmtVisitor* v)
{
        v->visitExpressionStmt(this);
}

void VarStmt::accept(StmtVisitor* v)
{
        v->visitVarStmt(this);
}

void BlockStmt::accept(StmtVisitor* v)
{
        v->visitBlockStmt(this);
}

void IfStmt::accept(StmtVisitor* v)
{
        v->visitIfStmt(this);
}

void WhileStmt::accept(StmtVisitor* v)
{
        v->visitWhileStmt(this);
}
