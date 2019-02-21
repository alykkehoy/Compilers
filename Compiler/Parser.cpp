#include "Parser.h"

Parser::Parser()
{
}

Parser::Parser(bool verbose_print)
{
	this->print = verbose_print;
}


Parser::~Parser()
{
}

void Parser::parse(Program& program)
{
	cout << endl << "INFO Parser - parsing program " << program.program_num << endl;
	current_program = program;
	current_token = program.tokens.begin();
	parse_block();
}

bool Parser::parse_block()
{
	match(L_BRACE);
	parse_statement_list();
	match(R_BRACE);
	return false;
}

bool Parser::parse_statement_list()
{
	return false;
}

bool Parser::parse_statement()
{
	return false;
}

bool Parser::parse_print_statement()
{
	return false;
}

bool Parser::parse_assignment_statement()
{
	return false;
}

bool Parser::parse_var_decl()
{
	return false;
}

bool Parser::match(TokenType token_type)
{
	bool return_val = current_token->token_type == token_type;
	if (!return_val) {
		cout << "TOKEN MISMATCH" << endl;
	}
	current_token++;
	return return_val;
}
