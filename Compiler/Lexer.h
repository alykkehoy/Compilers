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

	bool lex(string program_text);
};

