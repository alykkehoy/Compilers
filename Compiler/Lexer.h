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
	map<string, TokenType> token_map = { {"a", CHAR} };
	vector <list <Token>> tokens;

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

	//every token type has 2 functions associated with it
	//first is "is_tokentype" where the current text it checked against a token
	//second is "create_tokentype_token" where a token of that type is created and returned
	bool is_bracket(char character);
	Token create_bracket_token(char character, int line_num, int pos);

	bool is_operator(char character);
	Token create_operator_token(char character, int line_num, int pos);

	bool is_char(string program_text, int pos);
	Token create_char_token(char character, int line_num, int pos);

	bool is_digit(string program_text, int pos);
	Token create_digit_token(char character, int line_num, int pos);

	bool is_print(string program_text, int pos);
	Token create_print_token(int line_num, int pos);

	bool is_while(string program_text, int pos);
	Token create_while_token(int line_num, int pos);

	bool is_if(string program_text, int pos);
	Token create_if_token(int line_num, int pos);

	bool is_int(string program_text, int pos);
	Token create_int_token(int line_num, int pos);

	bool is_string(string program_text, int pos);
	Token create_string_token(int line_num, int pos);

	bool is_boolean(string program_text, int pos);
	Token create_boolean_token(int line_num, int pos);

	bool is_boolean_value(string program_text, int pos);
	Token create_boolean_value_token(char character, int line_num, int pos);

	bool is_boolean_operation(string program_text, int pos);
	Token create_boolean_operation_token(char character, int line_num, int pos);

	bool is_assignment(string program_text, int pos);
	Token create_assignment_token(int line_num, int pos);

	bool is_boolean_expression(char character);
	Token create_boolean_expression_token(char character, int line_num, int pos);

	bool is_string_expression(char character);
	Token create_string_expression_token(string text, int line_num, int pos);

	//find string end looks through a possible string expression and returns 2 things in a pair
	//first a boolean saying if it is a legitamte string expression in the grammer
	//second an integer for the position of the end of the string expression
	pair<bool, int> find_string_end(string program_text, int pos);
};

