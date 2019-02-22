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
	bool parse_while_statement();
	bool parse_if_statement();
	bool parse_expr();
	bool parse_int_expr();
	bool parse_string_expr();
	bool parse_boolean_expr();
	bool parse_id();
	bool parse_char_list();
	bool parse_type();
	bool parse_char();
	bool parse_space();
	bool parse_digit();
	bool parse_bool_op();
	bool parse_bool_val();
	bool parse_int_op();

	bool match(const TokenType& token_type);
	bool match(const vector<TokenType>& token_types);
};

