#include "levi_interp.hpp"

#include <vector>

/*
void LeviInterpreter::create()
{
	
}
*/

void LeviInterpreter::execute(const std::string& cmd)
{
	std::vector<Token> t = scanner.scan_tokens(cmd);
	std::vector<Stmt*> e = parser.parse(t);
	inter.Interpret(e);
}

