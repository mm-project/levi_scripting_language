#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum Token_type {
	LEFT_PAREN = 0, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

 	BANG, BANG_EQUAL,
  	EQUAL, EQUAL_EQUAL,
  	GREATER, GREATER_EQUAL,
  	LESS, LESS_EQUAL,
  // Literals.
  	IDENTIFIER, STRING, NUMBER,
  // Keywords.
  	AND, CLASS, ELSE, FALSE, FUNCTION, FOR, IF, NIL, OR,
  	PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

 	EOF_,
};

struct Token {
	Token(Token_type t, std::string l, int i): type(t), lexeme(l), line(i) {}
	Token_type type;
	std::string lexeme;
	int line;
};

#endif
