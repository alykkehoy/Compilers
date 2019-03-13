#include <string>
#pragma once

//this enum represents all the types of tokens that can be created
enum TokenType
{
	NONE,
	L_BRACE,
	R_BRACE,
	L_BOOL_EXP,
	R_BOOL_EXP,
	CHAR,
	ASSIGN_OP,
	I_TYPE,
	S_TYPE,
	B_TYPE,
	WHILE,
	IF,
	PRINT,
	DIGIT,
	BOOL,
	BOOL_OP,
	STRING_EXP,
	ADD,
	PROGRAM,
	BLOCK,
	STATEMENT_LIST,
	STATEMENT,
	PRINT_STATEMENT,
	ASSIGNMENT_STATEMENT,
	VAR_DECL,
	EXPR,
	WHILE_STATEMENT,
	IF_STATEMENT,
	EOP
};

using namespace std;

class Token
{
public:
	TokenType token_type = NONE;
	pair <int, int> position;
	int digit;
	int character;
	bool boolean;
	string text;

	Token();
	Token(TokenType token_type);
	~Token();

	string print_token_type(const TokenType& token_type);
};

