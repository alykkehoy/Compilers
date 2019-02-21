#pragma once

#include <vector>
#include <string>
#include "Token.h"

class Program
{
public:
	int program_num;
	string program_text;
	bool passed_lex = false;
	bool passed_parse = false;
	vector<Token> tokens;

	Program(int program_num, string program_text);
	~Program();
};

