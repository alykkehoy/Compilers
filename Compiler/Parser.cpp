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
	cout << "DEBUG Parser - parse block" << endl;
	return (match(L_BRACE) && parse_statement_list() && match(R_BRACE));
}

bool Parser::parse_statement_list()
{
	cout << "DEBUG Parser - parse statement list" << endl;

	//TODO
	//parse_statement();
	//parse_statement_list();
	
	return false;
}

//TODO
bool Parser::parse_statement()
{
	cout << "DEBUG Parser - parse statement" << endl;
	return false;
}

bool Parser::parse_print_statement()
{
	cout << "DEBUG Parser - parse print statement" << endl;
	return (match(PRINT) && match(L_BOOL_EXP) && parse_expr() && match(R_BOOL_EXP));
}

//TODO
bool Parser::parse_assignment_statement()
{
	cout << "DEBUG Parser - parse assignment statement" << endl;
	return false;
}

//TODO
bool Parser::parse_var_decl()
{
	cout << "DEBUG Parser - parse var decl" << endl;
	return false;
}

bool Parser::parse_while_statement()
{
	cout << "DEBUG Parser - parse while statement" << endl;
	return false;
}

bool Parser::parse_if_statement()
{
	cout << "DEBUG Parser - parse if statement" << endl;
	return false;
}

//TODO
bool Parser::parse_expr()
{
	cout << "DEBUG Parser - parse  expr" << endl;
	return false;
}

bool Parser::parse_int_expr()
{
	cout << "DEBUG Parser - parse int expr" << endl;
	return false;
}

bool Parser::parse_boolean_expr()
{
	cout << "DEBUG Parser - parse boolean expr" << endl;
	return false;
}

bool Parser::parse_id()
{
	cout << "DEBUG Parser - parse id" << endl;
	return false;
}

bool Parser::parse_char_list()
{
	cout << "DEBUG Parser - parse char list" << endl;
	return false;
}

bool Parser::parse_type()
{
	cout << "DEBUG Parser - parse type" << endl;
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
