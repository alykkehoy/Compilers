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
	Token create_bracket_token(char character);

	bool is_operator(char character);
	Token create_operator_token(char character);

	bool is_char(string program_text, int pos);
	Token create_char_token(char character);

	bool is_digit(string program_text, int pos);
	Token create_digit_token(char character);

	bool is_print(string program_text, int pos);
	Token create_print_token();

	bool is_while(string program_text, int pos);
	Token create_while_token();

	bool is_if(string program_text, int pos);
	Token create_if_token();

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
};

