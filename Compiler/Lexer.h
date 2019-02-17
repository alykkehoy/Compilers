#include <regex>
#include <string>
#include <list>
#include <iostream>
#include <map>
#include "Token.h"

#pragma once
using namespace std;
class Lexer
{
public:
	bool print = false;
	map<string, TokenType> token_map;
	vector <vector <Token>> tokens;

	Lexer();
	Lexer(bool print);
	~Lexer();
	void init_map();
	void lex(vector<string> programs);
	bool lex_single(string program_text);
	void remove_comments(string& program_text);
	void verbose_print(vector<Token> tokens);


	vector<Token> create_tokens(string program_text);
	vector<Token> validate_tokens(vector<Token> unvalidated_tokens);

	bool is_delimiter(string& program_text, int pos);

	bool is_bracket(char character);
	Token create_bracket_token(char character, int line_num, int pos);

	bool is_boolean_expression(char character);
	Token create_boolean_expression_token(char character, int line_num, int pos);

	bool is_string_expression(char character);

	//find string end looks through a possible string expression and returns 2 things in a pair
	//first a boolean saying if it is a legitamte string expression in the grammer
	//second an integer for the position of the end of the string expression
	pair<bool, int> find_string_end(string program_text, int pos);
};

