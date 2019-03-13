#include "Token.h"

Token::Token()
{
}

Token::Token(TokenType token_type)
{
	this->token_type = token_type;
}


Token::~Token()
{
}


string Token::print_token_type(const TokenType& token_type)
{
	string token_type_string;
	switch (token_type)
	{
	case R_BRACE:
		token_type_string = "R_BRACE";
		break;
	case L_BRACE:
		token_type_string = "L_BRACE";
		break;
	case R_BOOL_EXP:
		token_type_string = "R_BOOL_EXP";
		break;
	case L_BOOL_EXP:
		token_type_string = "L_BOOL_EXP";
		break;
	case WHILE:
		token_type_string = "WHILE";
		break;
	case IF:
		token_type_string = "IF";
		break;
	case S_TYPE:
		token_type_string = "S_TYPE";
		break;
	case I_TYPE:
		token_type_string = "I_TYPE";
		break;
	case B_TYPE:
		token_type_string = "B_TYPE";
		break;
	case ASSIGN_OP:
		token_type_string = "ASSIGN_OP";
		break;
	case PRINT:
		token_type_string = "PRINT";
		break;
	case BOOL:
		token_type_string = "BOOL";
		break;
	case BOOL_OP:
		token_type_string = "BOOL_OP";
		break;
	case ADD:
		token_type_string = "ADD";
		break;
	case CHAR:
		token_type_string = "CHAR";
		break;
	case DIGIT:
		token_type_string = "DIGIT";
		break;
	case STRING_EXP:
		token_type_string = "STRING_EXP";
		break;
	case PROGRAM:
		token_type_string = "PROGRAM";
		break;
	case BLOCK:
		token_type_string = "BLOCK";
		break;
	case STATEMENT_LIST:
		token_type_string = "STATEMENT_LIST";
		break;
	case STATEMENT:
		token_type_string = "STATEMENT";
		break;
	case PRINT_STATEMENT:
		token_type_string = "PRINT_STATEMENT";
		break;
	case ASSIGNMENT_STATEMENT:
		token_type_string = "ASSIGNMENT_STATEMENT";
		break;
	case VAR_DECL:
		token_type_string = "VARIABLE_DECLARATION";
		break;
	case EXPR:
		token_type_string = "EXPRESSION";
		break;
	case WHILE_STATEMENT:
		token_type_string = "WHILE_STATEMENT";
		break;
	case IF_STATEMENT:
		token_type_string = "IF_STATEMENT";
		break;
	case NONE:
		token_type_string = "NONE";
		break;
	default:
		token_type_string = "NOT FOUND";
		break;
	}
	return token_type_string;
}