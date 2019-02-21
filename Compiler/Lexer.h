#include <regex>
#include <string>
#include <list>
#include <iostream>
#include <map>

#include "Program.h"
#include "Token.h"

#pragma once
using namespace std;
class Lexer
{
public:
	bool print = false;
	map<string, TokenType> token_map;

	Lexer();
	Lexer(bool print);
	~Lexer();
	void init_map();
	void lex(vector<Program>& programs);
	void lex(Program& program);
	void remove_comments(string& program_text);
	void verbose_print(vector<Token> tokens);

	//create_tokens breaks down a string into word based on delimiters provided in the is_delimmiter function
	//it returns a vector of tokens that have not been validated
	void create_tokens(Program& program);

	//validate_tokens takes the unvalidated tokens and goes through checking their text against the map of keywords to tokentype enum
	//at the end it will display the errors it found 
	void validate_tokens(Program& program);

	//helper function to determin if a character is a delimiter or now
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

