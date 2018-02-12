#include "interpreter.hpp"

#include "environment.hpp"
#include "expr.hpp"
#include "error.hpp"
#include "stmt.hpp"

#include <iostream>

Interpreter::Interpreter()
{
        m_environment = new Environment();
}

std::string Interpreter::interpreter(Expr* e)
{
        try {
                Value value = evaluate(e);
                return value.Stringfy();
        } catch (Parser_error& error) {
                return error.what();
        }
}

Value Interpreter::evaluate(Expr* e)
{
        e->accept(this);
        return m_value;
}

void Interpreter::visitLiteral(Literal* e)
{
        m_value = e->m_literal;
}

void Interpreter::visitGrouping(Grouping* e)
{
        m_value = evaluate(e->m_grouping);
}

void Interpreter::visitUnary(Unary* e)
{
        Value right = evaluate(e->m_right);

        switch (e->m_operator.type) {
                case MINUS :
                        m_value = Value(-right.get_number());
                        break;
                case BANG :
                        m_value = Value(right.is_truthy());
                        break;
        }
        m_value = right;
}

void Interpreter::visitBinary(Binary* e)
{
        Value left = evaluate(e->m_left);
        Value right = evaluate(e->m_right);

        switch (e->m_operator.type) {
                case PLUS : {
                                    if (left.is_string() && right.is_string()) {
                                            m_value = Value(left.get_string() + right.get_string());
                                    } else if (left.is_number() && right.is_number()) {
                                            m_value = Value(left.get_number() + right.get_number());
                                    } else {
                                            throw Parser_error(e->m_operator,"Operands must be 2 string or numbers");
                                    }
                                    break;
                            }
                case MINUS : {
                                     checkOperands(e->m_operator, left, right);
                                     m_value = Value(left.get_number() - right.get_number());
                                     break;
                           }
                case SLASH : {
                                     checkOperands(e->m_operator, left, right);
                                     if (right.get_number() == 0) {
                                             throw Parser_error(e->m_operator, "Division to 0");
                                     }
                                     m_value = Value(left.get_number() / right.get_number());
                                     break;
                             }
                case STAR : {
                                     checkOperands(e->m_operator, left, right);
                                     m_value = Value(left.get_number() * right.get_number());
                                     break;
                            }
                case GREATER : {
                                     checkOperands(e->m_operator, left, right);
                                     m_value = Value(left.get_number() > right.get_number());
                                     break;
                               }
                case GREATER_EQUAL : {
                                     checkOperands(e->m_operator, left, right);
                                     m_value = Value(left.get_number() >= right.get_number());
                                     break;
                               }
                case LESS : {
                                     checkOperands(e->m_operator, left, right);
                                     m_value = Value(left.get_number() < right.get_number());
                                     break;
                               }
                case LESS_EQUAL : {
                                     checkOperands(e->m_operator, left, right);
                                     m_value = Value(left.get_number() <= right.get_number());
                                     break;
                               }
                case BANG_EQUAL : {
                                     checkOperands(e->m_operator, left, right);
                                     m_value = Value(!Value::is_equal(left,right));
                                     break;
                               }
                case EQUAL_EQUAL : {
                                     checkOperands(e->m_operator, left, right);
                                     m_value = Value(Value::is_equal(left,right));
                                     break;
                                   }
        }
}

void Interpreter::checkOperands(Token t,Value& v1,Value& v2)
{
        if (!v1.is_number() || !v2.is_number()) {
                throw Parser_error(t, "Operands must be number");
        }
}

void Interpreter::Interpret(std::vector<Stmt*> stmt)
{
        try {
                m_exception_happend = false;
                for (int i = 0; i < stmt.size(); ++i) {
                        if (m_exception_happend) {
                                break;
                        }
                        if (stmt[i] == 0) {
                                continue; //TODO : correct me, need because when var i; expression here is nil, need to create nil, not return 0;
                        }
                        execute(stmt[i]);
                }
        } catch (Parser_error& e) {
                std::cout << e.what() << std::endl;
        }
}

void Interpreter::execute(Stmt* s)
{
        s->accept(this);
}

void Interpreter::visitExpressionStmt(ExpressionStmt* s)
{
        evaluate(s->m_expression);
}

void Interpreter::visitPrintStmt(PrintStmt* s)
{
       m_value = evaluate(s->m_expression);
       if (m_exception_happend) { //case undifined variable
               return;
       }
       std::cout << m_value.Stringfy() << std::endl;
}

void Interpreter::visitVarStmt(VarStmt* s)
{
        Value v; //nil
        if (s->m_expression != 0) {
                v = evaluate(s->m_expression);
        }
        if (m_exception_happend) { // case var i = i;
                return;
        }
        // add name with value to enviorment
        try {
                m_environment->define(s->m_name.lexeme, v);
        } catch (Runtime_error& e) {
                m_exception_happend = true;
                std::cout << e.what() << std::endl;
        }
}

Value Interpreter::visitVariableExpr(VariableExpr* e)
{
        //enviromant lookup variable
        try {
                m_value = m_environment->get_variable(e->m_name.lexeme);
                return m_value;
        } catch (Runtime_error& e) {
                m_exception_happend = true;
                std::cout << e.what() << std::endl;
        }
        return Value();
}

Value Interpreter::visitAssignExpr(AssignExpr* e)
{
        Value value = evaluate(e->m_value);
        try {
                m_environment->assign(e->m_name, value);
                m_value = value;
        } catch (Runtime_error& e) {
                std::cout << e.what() << std::endl;
        }
        return value;
}

void Interpreter::visitBlockStmt(BlockStmt* s)
{
        executeBlock(s->m_stmts, new Environment(m_environment));
}

void Interpreter::executeBlock(std::vector<Stmt*> stmts, Environment* env)
{
        Environment* prev = m_environment;
        try {
                m_environment = env;
                for (auto it = stmts.begin(); it != stmts.end(); ++it) {
                        execute(*it);
                }
                m_environment = prev; //TODO: check me, I can be wrong
        } catch (Runtime_error& e) {
                m_environment = prev;
                //m_exception_happend = true;
                //std::cout << e.what() << std::endl;
        } catch (Parser_error& e) {
                m_environment = prev;
        }
        //delete prev;
}

void Interpreter::visitIfStmt(IfStmt* s)
{
        Value v = evaluate(s->m_condition);
        if (v.is_truthy()) {
                execute(s->m_then_branch);
        } else if (s->m_else_branch != 0) {
                execute(s->m_else_branch);
        }
}
