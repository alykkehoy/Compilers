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
	bool lex(string program_text);
	void remove_comments(string& program_text);
	void verbose_print(vector<Token> tokens);

	//create_tokens breaks down a string into word based on delimiters provided in the is_delimmiter function
	//it returns a vector of tokens that have not been validated
	vector<Token> create_tokens(string program_text);

	//validate_tokens takes the unvalidated tokens and goes through checking their text against the map of keywords to tokentype enum
	//at the end it will display the errors it found 
	vector<Token> validate_tokens(vector<Token> unvalidated_tokens);

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

