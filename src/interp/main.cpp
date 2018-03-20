#include <iostream>
#include <fstream>
#include <sstream>

#include <parser/scanner.hpp>
#include <parser/parser.hpp>
#include <parser/interpreter.hpp>

#include <util/fileio.hpp>

void run_file(const std::string& filename)
{
        std::string commands = util::read_file(filename);
        Scanner scanner;
        Parser parser;
        Interpreter inter;
        std::vector<Token> tokens = scanner.scan_tokens(commands);
        std::vector<Stmt*> stmts= parser.parse(tokens);
        inter.Interpret(stmts);
}

void run_prompt()
{
        std::cout << "=========================================================================="<< std::endl;
        std::cout << "================================ WELCOME ================================="<< std::endl;
        std::cout << "=========================================================================="<< std::endl;
        std::string line;
        Scanner scanner;
        Parser parser;
        Interpreter inter;
	for(;;) {
                line.clear();
		std::cout << ">";
		std::getline(std::cin, line);
                std::vector<Token> t = scanner.scan_tokens(line);
                std::vector<Stmt*> e = parser.parse(t);
                inter.Interpret(e);
	}
}

int main(int argc, char** argv)
{

	if (argc == 2) {
		run_file(argv[1]);
	} else {
		run_prompt();
	}
	return 0;
}
