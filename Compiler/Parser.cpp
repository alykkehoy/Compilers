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
	parse_statement();
	//parse_statement_list();
	
	return false;
}

bool Parser::parse_statement()
{
	cout << "DEBUG Parser - parse statement" << endl;
	if (current_token->token_type == PRINT) {
		return parse_print_statement();
	}
	else if (current_token->token_type == CHAR) {
		return parse_assignment_statement();
	}
	else if (current_token->token_type == WHILE) {
		return parse_while_statement();
	}
	else if (current_token->token_type == IF) {
		return parse_if_statement();
	}
	else if (current_token->token_type == L_BRACE) {
		return parse_block();
	}
	return false;
}

bool Parser::parse_print_statement()
{
	cout << "DEBUG Parser - parse print statement" << endl;
	return (match(PRINT) && match(L_BOOL_EXP) && parse_expr() && match(R_BOOL_EXP));
}

bool Parser::parse_assignment_statement()
{
	cout << "DEBUG Parser - parse assignment statement" << endl;
	return (parse_id() && match(ASSIGN_OP) && parse_expr());
}

bool Parser::parse_var_decl()
{
	cout << "DEBUG Parser - parse var decl" << endl;
	return (parse_type() && parse_id());
}

bool Parser::parse_while_statement()
{
	cout << "DEBUG Parser - parse while statement" << endl;
	return (match(WHILE) && parse_boolean_expr() && parse_block());
}

bool Parser::parse_if_statement()
{
	cout << "DEBUG Parser - parse if statement" << endl;
	return (match(IF) && parse_boolean_expr() && parse_block());
}

//TODO
bool Parser::parse_expr()
{
	cout << "DEBUG Parser - parse expr" << endl;
	return false;
}

//TODO
bool Parser::parse_int_expr()
{
	cout << "DEBUG Parser - parse int expr" << endl;
	return false;
}


bool Parser::parse_boolean_expr()
{
	cout << "DEBUG Parser - parse boolean expr" << endl;
	if (current_token->token_type == L_BOOL_EXP) {
		return (match(L_BOOL_EXP) && parse_expr() && parse_bool_op() && parse_expr() && match(R_BOOL_EXP));
	}
	return parse_bool_val();
}

//TODO
bool Parser::parse_id()
{
	cout << "DEBUG Parser - parse id" << endl;
	return false;
}

//TODO
bool Parser::parse_char_list()
{
	cout << "DEBUG Parser - parse char list" << endl;
	return false;
}

//TODO
bool Parser::parse_type()
{
	cout << "DEBUG Parser - parse type" << endl;
	return false;
}

bool Parser::parse_char()
{
	return false;
}

bool Parser::parse_space()
{
	return false;
}

bool Parser::parse_digit()
{
	return false;
}

bool Parser::parse_bool_op()
{
	return false;
}

bool Parser::parse_bool_val()
{
	return false;
}

bool Parser::parse_int_op()
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
