#include "scanner.hpp"

#include <cctype>
#include <iostream>

bool Scanner::is_at_end()
{
	return current >= source.length();
}

char Scanner::advance()
{
	++current;
	return source.at(current - 1);
}

void Scanner::add_token(Token_type type)
{
	std::string text = source.substr(start, current - start);
	Token new_token(type, text, line);
	tokens.push_back(new_token);
}

bool Scanner::match(char e)
{
	if (is_at_end()) return  false;
	if (source.at(current) != e) return false;
	++current;
	return  true;
}

char Scanner::peek()
{
	if (is_at_end()) return '\0';
	return source.at(current);
}

char Scanner::peek_next()
{
	if (current + 1 >= source.length()) return '\0';
	return source.at(current + 1);
}

void Scanner::number()
{
	while (isdigit(peek())) advance();
	if (peek() == '.' && isdigit(peek_next())) {
		advance();
		while (isdigit(peek())) advance();
	}
	tokens.push_back(Token(NUMBER, source.substr(start, current - start), line));
}

void Scanner::identifier()
{
	while (isalnum(peek())) advance();
	std::string text = source.substr(start, current - start);
        if (text == "print") {
                tokens.push_back(Token(PRINT, text, line));
        } else if (text == "true") {
                tokens.push_back(Token(TRUE, text, line));
        } else if (text == "false") {
                tokens.push_back(Token(FALSE, text, line));
        } else if (text == "var") {
                tokens.push_back(Token(VAR, text, line));
        } else if (text == "if") {
                tokens.push_back(Token(IF, text, line));
        } else if (text == "else") {
                tokens.push_back(Token(ELSE, text, line));
        } else if (text == "or") {
                tokens.push_back(Token(OR, text, line));
        } else if (text == "and") {
                tokens.push_back(Token(AND, text, line));
        } else if (text == "while") {
                tokens.push_back(Token(WHILE, text, line));
        } else if (text == "for") {
                tokens.push_back(Token(FOR, text, line));
        } else if (text == "function") {
                tokens.push_back(Token(FUNCTION, text, line));
        } else if (text == "return") {
                tokens.push_back(Token(RETURN, text, line));
        } else {
                tokens.push_back(Token(IDENTIFIER,text, line) );
        }
}

void Scanner::string()
{
	while (peek() != '"' && !is_at_end()) advance();
	if (is_at_end()) {
		std::cout <<" Error" <<std::endl;
		return;
	}
	advance();
	std::string text = source.substr(start + 1, current - start - 2);
	Token new_token(STRING, text, line);
	tokens.push_back(new_token);
}


void Scanner::scan_token()
{
	char c = advance();
	switch (c) {
		case ';' : add_token(SEMICOLON); break;
		case '(' : add_token(LEFT_PAREN); break;
		case ')' : add_token(RIGHT_PAREN); break;
		case '{' : add_token(LEFT_BRACE); break;
		case '}' : add_token(RIGHT_BRACE); break;
		case ',' : add_token(COMMA); break;
		case '.' : add_token(DOT); break;
		case '-' : add_token(MINUS); break;
		case '+' : add_token(PLUS); break;
		case '*' : add_token(STAR); break;
		case '!' : add_token(match('=') ? BANG_EQUAL : BANG); break;
		case '=' : add_token(match('=') ? EQUAL_EQUAL : EQUAL); break;
		case '<' : add_token(match('=') ? LESS_EQUAL : LESS); break;
		case '>' : add_token(match('=') ? GREATER_EQUAL : GREATER); break;
		case '/' : if (match('/')) {
          			while (!is_at_end()) advance();
     		 	} else {
          		add_token(SLASH);
        		} break;
		case ' ' :  //skip
                case '\t': break;

		case '"' : string(); break;

		default: if (isdigit(c)) {
				number();
			} else if (isAlpha(c) || c == '_') {
				identifier();
			} else {
				std::cout <<"EROOR" << std::endl;
			}
	}
}

std::vector<Token> Scanner::scan_tokens(std::string s)
{
        tokens.clear();
        source = s;
        start = 0;
        current = 0;
	while (!is_at_end()) {
		start = current;
		scan_token();
	}
	tokens.push_back(Token(EOF_, "END_OF_LINE", line));
        ++line;
	return tokens;
}

bool Scanner::isAlpha(char c)
{
	return (c >= 'a' && c <='z') || (c >= 'A' && c <= 'Z') || '_';
}
