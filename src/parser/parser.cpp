#include "parser.hpp"
#include "error.hpp"
#include "value.hpp"

bool Parser::is_at_end()
{
	return peek().type == EOF_;
}

Token Parser::peek()
{
	return m_tokens[m_current];
}

Token Parser::previous()
{
	return m_tokens[m_current - 1];
}

Token Parser::advance()
{
	if (!is_at_end()) {
		++m_current;
	}
	return previous();
}

Expr* Parser::expression()
{
	return assignment();
}

bool Parser::check(Token_type type)
{
	if(is_at_end()) return false;

	return peek().type == type;
}

bool Parser::match(Token_type type, Token_type type2, Token_type type3, Token_type type4)
{
	if (check(type)) {
		advance();
		return true;
	}
	if (check(type2)) {
		advance();
		return true;
	}
	if (check(type3)) {
		advance();
		return true;
	}
	if (check(type4)) {
		advance();
		return true;
	}
	return false;
}

Expr* Parser::assignment()
{
        Expr* expr = _or();

        if (match(EQUAL)) {
                Token eq = previous();
                Expr* value = expression();
                if (dynamic_cast<VariableExpr*>(expr)) {
                        Token name = dynamic_cast<VariableExpr*>(expr)->get_name();
                        return new AssignExpr(name, value);
                } else if (dynamic_cast<GetExpr*>(expr)) {
                        GetExpr* get_expr = static_cast<GetExpr*>(expr);
                        return new SetExpr(get_expr->m_expr, get_expr->m_name, value);
                }
                // report error
        }
        return expr;
}

Expr* Parser::equality()
{
	Expr* expr = comparison();

	while (match(BANG_EQUAL, EQUAL_EQUAL)) {
		Token op = previous();
		Expr* right = comparison();
		expr = new Binary(expr, op, right);
	}
	return expr;
}

Expr* Parser::comparison()
{
	Expr* expr = addition();

	while (match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
		Token op = previous();
		Expr* right = addition();
		expr = new Binary(expr, op, right);
	}
	return expr;
}

Expr* Parser::addition()
{
	Expr* expr = multiplication();

	while (match(MINUS, PLUS)) {
		Token op = previous();
		Expr* right = multiplication();
		expr = new Binary(expr, op, right);
	}
	return expr;
}

Expr* Parser::multiplication()
{
	Expr* expr = unary();

	while (match(SLASH, STAR)) {
		Token op = previous();
		Expr* right = unary();
	        expr = new Binary(expr, op, right);
	}
	return expr;
}

Expr* Parser::unary()
{
	if (match(BANG, MINUS)) {
		Token op = previous();
		Expr* right = unary();
	        return new Unary(op, right);
	}
        return call();
}

Expr* Parser::_function(std::string s)
{
        consume(LEFT_PAREN, "Expected ( name.");
        std::vector<Token> parameters;

        if (!check(RIGHT_PAREN)) {
               do {
                       if (parameters.size() >= 32) {
                               throw Parser_error(peek(), "max arguments");
                       }
                       parameters.push_back(consume(IDENTIFIER, "ident"));
               } while(match(COMMA));
        }
        consume(RIGHT_PAREN, "Expect ')' after parameters.");
        consume(LEFT_BRACE, "Expect '{' before function body.");
        std::vector<Stmt*> body = block();
        return new FunctionExpr(parameters, body);
}

Expr* Parser::call()
{
        Expr* e = primary();

        while (true) {
                if (match(LEFT_PAREN)) {
                        e = finishCall(e); //TODO: add identifier
                } else if (match(DOT)) {
                        Token name = consume(IDENTIFIER, "Expect property name after '.'.");
                        e = new GetExpr(e, name);
                } else {
                        break;
                }
        }
        return e;
}

Expr* Parser::finishCall(Expr* callee)
{
        std::vector<Expr*> arguments;

        if (!check(RIGHT_PAREN)) {
                do {
                        arguments.push_back(expression());
                } while (match(COMMA));
        }
        //TODO: add max arguments checking
        Token paren = consume(RIGHT_PAREN, "Expect ')' apter arguments.");
        FunctionExpr* func = static_cast<FunctionExpr*>(callee);
        if (func->parameters_size() != arguments.size()) {
                //throw Error;
        }
        return new CallExpr(callee, paren, arguments);
}

Expr* Parser::primary()
{
	if (match(FALSE)) return new Literal(Value(false));
    	if (match(TRUE)) return new Literal(Value(true));
    	if (match(NIL)) return new Literal(Value("null"));

    	if (match(NUMBER)) {
     		 return new Literal(Value(std::stod(previous().lexeme)));
    	}
        if (match(STRING)) {
                        return new Literal(Value(previous().lexeme));
        }
        if (match(IDENTIFIER)) {
                return new VariableExpr(previous());
        }
        if (match(FUNCTION)) {
                return _function("function");
        }
    	if (match(LEFT_PAREN)) {
  		Expr* expr = expression();
		consume(RIGHT_PAREN, "expect ')' ");
    		return new Grouping(expr);
    	}

	throw Parser_error(peek(), "expect expression.");
}

Token Parser::consume(Token_type t, std::string s)
{
	if (check(t)) return advance();

	throw Parser_error(peek(), s);
}

std::vector<Stmt*> Parser::parse(std::vector<Token> t)
{
        m_current = 0;
        m_tokens.clear();
        m_tokens = t;
        std::vector<Stmt*> stmt;
        while (!is_at_end()) {
                stmt.push_back(declaration());
        }
        return stmt;
}

void Parser::synchronize()
{
	advance();
	while(!is_at_end()) {
		if (previous().type == SEMICOLON) return;

		switch (peek().type) {
			case CLASS:
			case IF:
			case WHILE:
			case VAR:
			case FUNCTION:
			case FOR:
			case PRINT:
			case RETURN:
				return;
		}
		advance();
	}
}

Stmt* Parser::statement()
{
        if (match(IF)) return ifStmt();

        if (match(FOR)) return forStatement();

        if (match(PRINT)) return printStmt();

        if (match(RETURN)) return returnStmt();

        if (match(WHILE)) return whileStatement();

        if (match(LEFT_BRACE)) return new BlockStmt(block());

        return expressionStmt();
}

Stmt* Parser::printStmt()
{
        Expr* expr = expression();
        consume(SEMICOLON, "Expect ';' after Print stmt.");
        return new PrintStmt(expr);
}

Stmt* Parser::expressionStmt()
{
        Expr* expr = expression();
        consume(SEMICOLON, "Expect ';' after expression.");
        return new ExpressionStmt(expr);
}

Stmt* Parser::declaration()
{
        try {
                if (match(CLASS)) return classDeclaration();
                if (match(FUNCTION)) return functionDeclaration("function");
                if (match(VAR)) return varDeclaration();
                return statement();
        } catch (Parser_error& e) {
                std::cout << e.what() << std::endl;
                synchronize();
                return 0;
        }
}

Stmt* Parser::functionDeclaration(std::string s)
{
        Token name = consume(IDENTIFIER, "Expect function name.");
        FunctionExpr* fexpr = static_cast<FunctionExpr*>(_function(s));
        return new FunctionStmt(name, fexpr);
}

Stmt* Parser::varDeclaration()
{
        Token name = consume(IDENTIFIER, "Expect variable name.");
        Expr* init = 0;
        if (match(EQUAL)) {
                init = expression();
        }
        consume(SEMICOLON, "Expect ';' after variable declaration.");
        return new VarStmt(name, init);
}

std::vector<Stmt*> Parser::block()
{
        std::vector<Stmt*> stmts;

        while (!check(RIGHT_BRACE) && !is_at_end()) {
                stmts.push_back(declaration());
        }
        consume(RIGHT_BRACE, "Expect '}' after block.");
        return stmts;
}

Stmt* Parser::ifStmt()
{
        consume(LEFT_PAREN, "Expect '(' before if condition.");
        Expr* condition = expression();
        consume(RIGHT_PAREN, "Expect ')' after if condition.");

        Stmt* then_branch = statement();
        Stmt* else_branch = 0;

        if (match(ELSE)) {
                else_branch = statement();
        }

        return new IfStmt(condition, then_branch, else_branch);
}

Expr* Parser::_or()
{
        Expr* e = _and();

        while (match(OR)) {
                Token op = previous();
                Expr* right = _and();
                e = new LogicalExpr(e, op, right);
        }
        return e;
}

Expr* Parser::_and()
{
        Expr* e = equality();

        while (match(AND)) {
                Token op = previous();
                Expr* right = equality();
                e = new LogicalExpr(e, op, right);
        }
        return e;
}

Stmt* Parser::whileStatement()
{
        consume(LEFT_PAREN, "Expect '(' before 'while'.");
        Expr* condition = expression();
        consume(RIGHT_PAREN, "Expect ')' after 'while'.");
        Stmt* body = statement();
        return new WhileStmt(condition, body);
}

Stmt* Parser::forStatement()
{
        consume(LEFT_PAREN, "Expect '(' before 'for' loop.");

        Stmt* initializer;
        if (match(SEMICOLON)) {
                initializer = 0;
        } else if (match(VAR)) {
                initializer = varDeclaration();
        } else {
                initializer = expressionStmt();
        }

        Expr* condition = 0;
        if (!check(SEMICOLON)) {
                condition = expression();
        }
        consume(SEMICOLON, "Expect ';' after condition in for loop");

        Expr* increment = 0;
        if (!check(RIGHT_PAREN)) {
                increment = expression();
        }
        consume(RIGHT_PAREN, "Expect ')' after 'for loop'.");

        Stmt* body = statement();

        if (increment != 0 ) {
                body = new BlockStmt({body, new ExpressionStmt(increment)});
        }

        if (condition == 0) {
                condition = new Literal(Value(true));
        }

        body = new WhileStmt(condition, body);
        if (initializer != 0) {
                body = new BlockStmt({initializer, body});
        }
        return body;
}

Stmt* Parser::returnStmt()
{
        Token name = previous();
        Expr* value;
        if (!check(SEMICOLON)) {
                value = expression();
        }

        consume(SEMICOLON, "Expected ';' after return.");
        return new ReturnStmt(name, value);
}

Stmt* Parser::classDeclaration()
{
        Token name = consume(IDENTIFIER, "Expect class name.");
        consume(LEFT_BRACE, "Expect '{' before class body.");
        std::vector<FunctionStmt*> methods;
        while (!check(RIGHT_BRACE) && !is_at_end()) {
                //advance(); // check need this here?
                methods.push_back(static_cast<FunctionStmt*>(functionDeclaration("method")));
        }
        consume(RIGHT_BRACE, "Expect '}' after class body.");
        return new ClassStmt(name, methods);
}

