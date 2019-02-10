#include "Lexer.h"

Lexer::Lexer()
{
}


Lexer::~Lexer()
{
}

void Lexer::lex(vector <string> programs)
{
	int prog_count = 1;
	while (!programs.empty()) {
		cout << "INFO Lexer - lexing program " << prog_count << endl;
		lex_single(programs.front());
		programs.erase(programs.begin());
		prog_count++;
	}
	return;
}

bool Lexer::lex_single(string program_text) {
	int errors = 0;
	int line_num = 0;
	list <Token> program_tokens;

	remove_comments(program_text);
	for (int i = 0; i < program_text.length(); i++) {
		if (program_text[i] == '\n') {
			line_num++;
		}
		else if (is_bracket(program_text[i])) {
			create_bracket_token(program_text[i]);
			cout << "DEBUG Lexer - Brace [ " << program_text[i] << " ] found at (" << line_num << ":" << i << ")" << endl;
		}
		else if (is_operator(program_text[i])) {
			create_operator_token(program_text[i]);
			cout << "DEBUG Lexer - Operator [ " << program_text[i] << " ] found at (" << line_num << ":" << i << ")" << endl;
		}
		else if (is_print(program_text, i)) {
			cout << "DEBUG Lexer - Print [ print ] found at (" << line_num << ":" << i << ")" << endl;
			i = i + 5;
		}
		else if (is_digit(program_text, i)) {
			create_digit_token(program_text[i]);
			cout << "DEBUG Lexer - Digit [ " << program_text[i] << " ] found at (" << line_num << ":" << i << ")" << endl;
		}
		else if (is_char(program_text, i)) {
			create_char_token(program_text[i]);
			cout << "DEBUG Lexer - Char [ " << program_text[i] << " ] found at (" << line_num << ":" << i << ")" << endl;
		}
		else {
			cout << "ERROR Lexer - Error (" << line_num << ":" << i << ") unrecognized token: " << program_text[i] << endl;
			errors++;
		}
	}

	if (errors > 0) {
		cout << "INFO Lexer - Lex failed with " << errors << " errors" << endl << endl;
		return false;
	}
	//cout << program_text << endl;
	cout << "INFO Lexer - Lex complete with 0 errors" << endl << endl;
	tokens.push_back(program_tokens);
	return true;
}

void Lexer::remove_comments(string& program_text)
{
	while (program_text.find("/*") != string::npos) {
		int start = program_text.find("/*");
		int end = program_text.find("*/") - start + 2;

		if (program_text.find("*/") == string::npos) {
			cout << "WARNING Lexer - no comment end found" << endl;
			end = -1;
		}
		program_text.erase(start, end);
	}
	//cout << program_text << endl;
}

bool Lexer::is_bracket(char character)
{
	return (character == '{' || character == '}');
}

void Lexer::create_bracket_token(char character)
{
}

bool Lexer::is_operator(char character)
{
	return (character == '+');
}

void Lexer::create_operator_token(char character)
{
}

bool Lexer::is_char(string program_text, int pos)
{
	return (isalpha(program_text[pos]) && !isalpha(program_text[pos + 1]));
}

void Lexer::create_char_token(char character)
{
}

bool Lexer::is_digit(string program_text, int pos)
{
	return (isdigit(program_text[pos]) && !isalnum(program_text[pos + 1]));
}

void Lexer::create_digit_token(char character)
{
}

bool Lexer::is_print(string program_text, int pos)
{
	return (program_text.compare(pos, 5, "print") == 0);
}
