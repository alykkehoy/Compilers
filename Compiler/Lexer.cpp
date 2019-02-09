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

	if (errors > 0) {
		cout << "INFO Lexer - Lex failed with " << errors << " errors" << endl;
		//exit(1);
		return false;
	}
	cout << "INFO Lexer - Lex complete with 0 errors" << endl;
	return true;
}
