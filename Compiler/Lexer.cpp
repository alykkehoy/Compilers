#include "Lexer.h"

Lexer::Lexer()
{
}


Lexer::~Lexer()
{
}

bool Lexer::lex(string program_text)
{
	int errors = 0;
	bool return_status = true;
	list <Token> program_tokens;

	if (errors > 0) {
		cout << "INFO Lexer - Lex failed with " << errors << " errors" << endl;
		return_status = false;
	}
	//cout << program_text << endl;
	cout << "INFO Lexer - Lex complete with 0 errors" << endl;
	tokens.push_back(program_tokens);
	return return_status;
}
