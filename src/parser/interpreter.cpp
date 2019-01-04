#include "interpreter.hpp"

#include "class_instance.hpp"
#include "environment.hpp"
#include "expr.hpp"
#include "error.hpp"
#include "stmt.hpp"
#include "native_functions.hpp"
#include "callable.hpp"
#include "class.hpp"
#include "function.hpp"
#include "return.hpp"

#include <iostream>

Interpreter::Interpreter(): m_globals(new Environment())
{
        m_globals->define("time", Value(new ClockFunction()));
        m_environment = m_globals;
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
                for (unsigned i = 0; i < stmt.size(); ++i) {
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

void Interpreter::visitVariableExpr(VariableExpr* e)
{
        //enviromant lookup variable
        try {
                m_value = m_environment->get_variable(e->m_name.lexeme);
        } catch (Runtime_error& e) {
                m_value = "";
                m_exception_happend = true;
                std::cout << e.what() << std::endl;
        }
}

void Interpreter::visitAssignExpr(AssignExpr* e)
{
        Value value = evaluate(e->m_value);
        try {
                m_environment->assign(e->m_name.lexeme, value);
                m_value = value;
        } catch (Runtime_error& e) {
                std::cout << e.what() << std::endl;
        }
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
                m_environment = prev;
        } catch (Runtime_error& e) {
                m_environment = prev;
                //m_exception_happend = true;
                //std::cout << e.what() << std::endl;
        } catch (Parser_error& e) {
                m_environment = prev;
        } catch(Return& e) {
                m_environment = prev; //TODO: fixme
                throw e;
        }
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

void Interpreter::visitLogicalExpr(LogicalExpr* e)
{
        Value left = evaluate(e->m_left);

        if (e->m_operator.type == OR) {
                if (left.is_truthy()) {
                        m_value = left;
                }
        } else if (!left.is_truthy()) {
                        m_value = left;
        }
        Value right = evaluate(e->m_right);
        m_value = right;
}

void Interpreter::visitWhileStmt(WhileStmt* s)
{
        Value v = evaluate(s->m_condition);
        while (v.is_truthy()) {
                execute(s->m_body);
                v = evaluate(s->m_condition);
        }
}

void Interpreter::visitCallExpr(CallExpr* e)
{
        Value callee = evaluate(e->m_callee);

        // check if callee is callable
        std::vector<Value> args;
        Callable* callable = callee.get_callable();
        try {
                if (callable->arity() != e->m_arguments.size()) {
                        throw Runtime_error("wrong arguments");
                }
                for (unsigned i = 0; i < e->m_arguments.size(); ++i) {
                        args.push_back(evaluate(e->m_arguments[i]));
                }
                m_value = callable->call(this, args);
        } catch(Runtime_error& e) {
                std::cout << e.what() << std::endl;
        }
}

void Interpreter::visitFunctionExpr(FunctionExpr* e)
{
        Function* fun= new Function(e, m_environment, false);
        m_value = Value(fun);
}

void Interpreter::visitFunctionStmt(FunctionStmt* e)
{
        Function* fun = new Function(e->m_declaration, m_environment, false, e->m_name.lexeme);
        m_environment->define(e->m_name.lexeme, Value(fun));
}

void Interpreter::visitReturnStmt(ReturnStmt* e)
{
        Value value;
        if (e->m_value != 0) {
                value = evaluate(e->m_value);
        }
        throw Return(value);
}

void Interpreter::visitClassStmt(ClassStmt* e)
{
        std::map<std::string, Function*> methods;
        for (auto it = e->m_methods.begin(); it != e->m_methods.end(); ++it) {
                Function* function = new Function((*it)->m_declaration, m_environment, false);
                methods[e->m_name.lexeme] = function;
        }
        Class* klass = new Class(e->m_name.lexeme, methods);
        m_environment->define(e->m_name.lexeme, Value(klass));
}

void Interpreter::visitGetExpr(GetExpr* e)
{
        Value object = evaluate(e->m_expr);
        if (object.is_instance()) {
                m_value = object.get_instance()->get(e->m_name);
                return;
        }
        throw Runtime_error("Get - Only instances have properties.");
}

void Interpreter::visitSetExpr(SetExpr* e)
{
        Value object = evaluate(e->m_object);
        if (object.is_instance()) {
                m_value = evaluate(e->m_value);
                object.get_instance()->set(e->m_name, m_value);
                return;
        }
        throw Runtime_error("Set - Only instances have properties.");
}

