#ifndef LEVI_INTERP_HPP
#define LEVI_INTERP_HPP


#include "../parser/scanner.hpp"
#include "../parser/parser.hpp"
#include "../parser/interpreter.hpp"

#include <string>

class LeviInterpreter
{
	public: 
		void execute(const std::string& str);
		//void init();
		//void utem();
		/*ELEN ADD HERE ANY INTEGRATION YOU WANT*/
	
	private:
		Scanner scanner;
		Parser parser;
		Interpreter inter;
};

#endif
