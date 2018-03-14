#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <vector>
#include <map>

#include "token.hpp"

class Scanner {
public:
	//Scanner(std::string source):source(source), start(0), current(0), line(1) {}

        Scanner() : line(1) {}
	std::vector<Token> scan_tokens(std::string);
private:
	void scan_token();
	bool is_at_end();
	bool match(char);
	char advance();
	void add_token(Token_type);

	void number();
	void identifier();
	void string();

	bool isAlpha(char);

	char peek();
	char peek_next();

	std::string source;
	std::vector<Token> tokens;
	size_t start;
	size_t current;
	size_t line;
};

#endif
