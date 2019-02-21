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
}

bool Parser::parse_block()
{
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

bool Parser::match(TokenType)
{
	return false;
}
