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
	current_program = &program;
	current_token = program.tokens.begin();
	current_node = &program.cst.head;

	if (parse_block()) {
		//if the parse finishes with all the tokens consumed
		if (current_token == current_program->tokens.end()) {
			cout << "Parse complete" << endl;
			current_program->passed_parse = true;
		}
		//if the parse finishes, but there are leftover tokens
		else {
			cout << "ERROR PARSER - TOKEN MISMATCH at (" << current_token->position.first << ":"
				<< current_token->position.second << ") expected: NONE found: "
				<< current_token->print_token_type(current_token->token_type) << endl;
			cout << "Parse failed" << endl;
		}
	}
	//if the parse fails
	else {
		cout << "Parse failed" << endl;
		current_program->passed_parse = false;
	}
}

bool Parser::parse_block()
{
	cout << "DEBUG Parser - parse block" << endl;

	current_node = current_program->cst.create_node(current_node, BLOCK);
	bool return_val = (match(L_BRACE) && parse_statement_list() && match(R_BRACE));
	current_node = current_node->parent;

	return return_val;
}

bool Parser::parse_statement_list()
{
	cout << "DEBUG Parser - parse statement list" << endl;
	current_node = current_program->cst.create_node(current_node, STATEMENT_LIST);
	bool return_val = true;

	if (current_token != current_program->tokens.end()) {
		if (is_statement()) {
			return_val = (parse_statement() && parse_statement_list());
		}
	}

	current_node = current_node->parent;
	return return_val;
}

bool Parser::parse_statement()
{
	cout << "DEBUG Parser - parse statement" << endl;

	current_node = current_program->cst.create_node(current_node, STATEMENT);
	bool return_val = false;

	if (current_token != current_program->tokens.end()) {
		if (current_token->token_type == PRINT) {
			return_val = parse_print_statement();
		}
		else if (current_token->token_type == CHAR) {
			return_val = parse_assignment_statement();
		}
		else if (current_token->token_type == I_TYPE
			|| current_token->token_type == S_TYPE
			|| current_token->token_type == B_TYPE) {
			return_val = parse_var_decl();
		}
		else if (current_token->token_type == WHILE) {
			return_val = parse_while_statement();
		}
		else if (current_token->token_type == IF) {
			return_val = parse_if_statement();
		}
		else if (current_token->token_type == L_BRACE) {
			return_val = parse_block();
		}
	}

	current_node = current_node->parent;
	return return_val;
}

bool Parser::parse_print_statement()
{
	cout << "DEBUG Parser - parse print statement" << endl;

	current_node = current_program->cst.create_node(current_node, PRINT_STATEMENT);
	bool return_val = (match(PRINT) && match(L_BOOL_EXP) && parse_expr() && match(R_BOOL_EXP));
	current_node = current_node->parent;

	return return_val;
}

bool Parser::parse_assignment_statement()
{
	cout << "DEBUG Parser - parse assignment statement" << endl;

	current_node = current_program->cst.create_node(current_node, ASSIGNMENT_STATEMENT);
	bool return_val = (parse_id() && match(ASSIGN_OP) && parse_expr());
	current_node = current_node->parent;

	return return_val;
}

bool Parser::parse_var_decl()
{
	cout << "DEBUG Parser - parse var decl" << endl;

	current_node = current_program->cst.create_node(current_node, VAR_DECL);
	bool return_val = (parse_type() && parse_id());
	current_node = current_node->parent;

	return return_val;
}

bool Parser::parse_while_statement()
{
	cout << "DEBUG Parser - parse while statement" << endl;

	current_node = current_program->cst.create_node(current_node, WHILE_STATEMENT);
	bool return_val = (match(WHILE) && parse_boolean_expr() && parse_block());
	current_node = current_node->parent;

	return return_val;
}

bool Parser::parse_if_statement()
{
	cout << "DEBUG Parser - parse if statement" << endl;

	current_node = current_program->cst.create_node(current_node, IF_STATEMENT);
	bool return_val = (match(IF) && parse_boolean_expr() && parse_block());
	current_node = current_node->parent;

	return return_val;
}

bool Parser::parse_expr()
{
	cout << "DEBUG Parser - parse expr" << endl;

	current_node = current_program->cst.create_node(current_node, EXPR);
	bool return_val = false;

	if (current_token != current_program->tokens.end()) {
		if (current_token->token_type == DIGIT) {
			return_val = parse_int_expr();
		}
		else if (current_token->token_type == STRING_EXP) {
			return_val = parse_string_expr();
		}
		else if (current_token->token_type == L_BOOL_EXP
			|| current_token->token_type == BOOL) {
			return_val = parse_boolean_expr();
		}
		else if (current_token->token_type == CHAR) {
			return_val = parse_id();
		}
	}

	current_node = current_node->parent;
	return return_val;
}

bool Parser::parse_int_expr()
{
	cout << "DEBUG Parser - parse int expr" << endl;

	current_node = current_program->cst.create_node(current_node, INT_EXPR);
	bool return_val = false;
	if (current_token != current_program->tokens.end()
		&& (current_token + 1) != current_program->tokens.end()) {
		if ((current_token + 1)->token_type == ADD) {
			return_val = parse_digit() && parse_int_op() && parse_expr();
		}
		else {
			return_val = parse_digit();
		}
	}

	current_node = current_node->parent;
	return return_val;
}

bool Parser::parse_string_expr()
{
	cout << "DEBUG Parser - parse string expr" << endl;
	return match(STRING_EXP);
}

bool Parser::parse_boolean_expr()
{
	cout << "DEBUG Parser - parse boolean expr" << endl;

	current_node = current_program->cst.create_node(current_node, BOOL_EXPR);
	bool return_val = false;

	if (current_token != current_program->tokens.end()) {
		if (current_token->token_type == L_BOOL_EXP) {
			return_val = (match(L_BOOL_EXP) && parse_expr() && parse_bool_op() && parse_expr() && match(R_BOOL_EXP));
		}
		else {
			return_val = parse_bool_val();
		}
	}

	current_node = current_node->parent;
	return return_val;
}

bool Parser::parse_id()
{
	cout << "DEBUG Parser - parse id" << endl;
	return match(CHAR);
}

//NEEDS FIXED
bool Parser::parse_char_list()
{
	cout << "DEBUG Parser - parse char list" << endl;
	return match(STRING_EXP);
}

bool Parser::parse_type()
{
	cout << "DEBUG Parser - parse type" << endl;
	return match(vector<TokenType> {I_TYPE, S_TYPE, B_TYPE});
}

bool Parser::parse_char()
{
	cout << "DEBUG Parser - parse char" << endl;
	return match(CHAR);
}

bool Parser::parse_digit()
{
	cout << "DEBUG Parser - parse digit" << endl;
	return match(DIGIT);
}

bool Parser::parse_bool_op()
{
	cout << "DEBUG Parser - parse bool op" << endl;
	return match(BOOL_OP);
}

bool Parser::parse_bool_val()
{
	cout << "DEBUG Parser - parse bool val" << endl;
	return match(BOOL);
}

bool Parser::parse_int_op()
{
	cout << "DEBUG Parser - parse int op" << endl;
	return match(ADD);
}

bool Parser::is_statement()
{
	vector<TokenType> types = { PRINT, CHAR, I_TYPE, S_TYPE, B_TYPE, WHILE, IF, L_BRACE };
	
	for (int i = 0; i < types.size(); i++) {
		if (current_token->token_type == types[i]) {
			return true;
		}
	}

	return false;
}

bool Parser::match(const TokenType& token_type)
{
	if (current_token == current_program->tokens.end()) {
		cout << "ERROR PARSER - TOKEN MISMATCH expected: " << Token::print_token_type(token_type) << " found: NONE" << endl;
		return false;
	}
	bool return_val = current_token->token_type == token_type;
	if (!return_val) {
		cout << "ERROR PARSER - TOKEN MISMATCH at (" << current_token->position.first << ":" 
			 << current_token->position.second << ") expected: " << current_token->print_token_type(token_type) << " found: " 
			 << current_token->print_token_type(current_token->token_type) << endl;
	}

	current_program->cst.create_node(current_node, token_type, &(*current_token));

	current_token++;
	return return_val;
}

bool Parser::match(const vector<TokenType>& token_types)
{
	TokenType token_type = NONE;
	for (int i = 0; i < token_types.size(); i++) {
		if (current_token->token_type == token_types[i]) {
			token_type = token_types[i];
		}
	}
	return match(token_type);
}
