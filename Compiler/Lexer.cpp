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
	bool return_status = true;
	list <Token> program_tokens;

	remove_comments(program_text);

	for (int i = 0; i < program_text.length(); i++) {
		if (program_text[i] == '\n') {
			line_num++;
		}
		if (is_bracket(program_text[i])) {
			create_bracket_token(program_text[i]);
			cout << "DEBUG Lexer - Brace [ " << program_text[i] << " ] found at (" << line_num << ":" << i << ")" << endl;
		}
		if (is_operator(program_text[i])) {
			create_operator_token(program_text[i]);
			cout << "DEBUG Lexer - Operator [ " << program_text[i] << " ] found at (" << line_num << ":" << i << ")" << endl;
		}
	}

	if (errors > 0) {
		cout << "INFO Lexer - Lex failed with " << errors << " errors" << endl;
		return_status = false;
	}
	//cout << program_text << endl;
	cout << "INFO Lexer - Lex complete with 0 errors" << endl;
	tokens.push_back(program_tokens);
	return return_status;
}

void Lexer::remove_comments(string program_text)
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
