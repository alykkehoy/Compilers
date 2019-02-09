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
	ADD,
	EOP
};

using namespace std;

class Token
{
public:
	string regex_string;
	pair <int, int> position;

	Token();
	~Token();
};

