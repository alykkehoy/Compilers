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
	void remove_comments(string& program_text);

	bool is_bracket(char character);
	void create_bracket_token(char character);

	bool is_operator(char character);
	void create_operator_token(char character);

	bool is_char(string program_text, int pos);
	void create_char_token(char character);

	bool is_digit(string program_text, int pos);
	void create_digit_token(char character);

	bool is_print(string program_text, int pos);
	void create_print_token();

	bool is_while(string program_text, int pos);
	void create_while_token();

	bool is_if(string program_text, int pos);
	void create_if_token();

};

