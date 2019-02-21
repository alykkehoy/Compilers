#pragma once

#include <vector>
#include <iostream>

#include "Token.h"
#include "Program.h"

using namespace std;

class Parser
{
public:
	bool print = false;
	Program empty_program;
	Program& current_program = empty_program;
	vector<Token>::iterator current_token = empty_program.tokens.begin();

	Parser();
	Parser(bool verbose_print);
	~Parser();

	void parse(Program& program);

private:
	bool parse_block();
	bool parse_statement_list();
	bool parse_statement();
	bool parse_print_statement();
	bool parse_assignment_statement();
	bool parse_var_decl();

	bool match(TokenType token_type);
};

