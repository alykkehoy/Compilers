#pragma once

#include <vector>
#include <string>
#include "Token.h"
#include "Tree.h"

class Program
{
public:
	int program_num;
	string program_text;
	bool passed_lex = false;
	bool passed_parse = false;
	bool passes_semantic_analysis = false;
	vector<Token> tokens;
	Tree cst;
	Tree ast;
	scope scope_tree;

	Program();
	Program(int program_num, string program_text);
	~Program();
};

