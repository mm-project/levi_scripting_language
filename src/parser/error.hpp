#ifndef _error_hpp_
#define _error_hpp_

#include "token.hpp"

#include <stdexcept>

struct Parser_error : public std::runtime_error
{
	Parser_error(Token t, std::string s) : runtime_error(s), token(t) {}

	virtual ~Parser_error() throw() {}

	Token token;
};

struct Runtime_error : public std::runtime_error
{
        Runtime_error(std::string n) : runtime_error(n) {}

        virtual ~Runtime_error() throw() {}
};

#endif
