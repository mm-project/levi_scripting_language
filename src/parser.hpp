#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.hpp"
#include "expr.hpp"
#include "stmt.hpp"

#include <vector>
#include <string>
#include <iostream>

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

        std::vector<Stmt*> block();
        Stmt* declaration();
        Stmt* statement();
        Stmt* printStmt();
        Stmt* expressionStmt();
        Stmt* varDeclaration();
        Stmt* ifStmt();

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
