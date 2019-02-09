#include <regex>
#include <string>
#include <list>
#include <iostream>
#include "Token.h"

#pragma once
using namespace std;
class Lexer
{
public:
	vector <list <Token>> tokens;

	Lexer();
	~Lexer();
	void lex(vector<string> programs);
	bool lex_single(string program_text);
	void remove_comments(string program_text);
};

