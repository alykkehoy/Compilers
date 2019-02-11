#include <string>
#pragma once

enum TokenType
{
	L_BRACE,
	R_BRACE,
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
	ADD,
	EOP
};

using namespace std;

class Token
{
public:
	TokenType token_type;
	pair <int, int> position;
	int digit;
	int character;
	bool boolean;

	Token();
	Token(TokenType token_type);
	~Token();
};

