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
	bool return_status = true;
	list <Token> program_tokens;

	remove_comments(program_text);

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
		program_text.erase(start, end);
	}
	cout << program_text << endl;
}
