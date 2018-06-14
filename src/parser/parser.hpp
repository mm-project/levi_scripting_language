#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.hpp"
#include "expr.hpp"
#include "stmt.hpp"

#include <vector>
#include <string>
#include <iostream>

/// @class Parser
class Parser {
public:
	Parser() {m_current = 0;}
        std::vector<Stmt*> parse(std::vector<Token> t);

private:
        Expr* assignment();
	Expr* expression();
	Expr* equality();
	Expr* comparison();
	Expr* addition();
	Expr* multiplication();
	Expr* unary();
	Expr* primary();
        Expr* call();
        Expr* finishCall(Expr*);
        Expr* _function(std::string);

        Expr* _or();
        Expr* _and();


        std::vector<Stmt*> block();
        Stmt* declaration();
        Stmt* statement();
        Stmt* printStmt();
        Stmt* expressionStmt();
        Stmt* varDeclaration();
        Stmt* ifStmt();
        Stmt* whileStatement();
        Stmt* forStatement();
        Stmt* functionDeclaration(std::string);
        Stmt* returnStmt();
        Stmt* classDeclaration();

	bool match(Token_type type = EOF_, Token_type type2 = EOF_, Token_type type3 = EOF_, Token_type type4 = EOF_);
	bool check(Token_type);
	bool is_at_end();
	Token advance();
	Token peek();
	Token previous();
	Token consume(Token_type, std::string);
	void synchronize();

	std::vector<Token> m_tokens;
	int m_current;
};

#endif
