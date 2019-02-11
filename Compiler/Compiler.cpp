#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#include "Token.h"
#include "Lexer.h"

using namespace std;

string readFile(string file_name) {
	ifstream file(file_name);
	string text_line;
	string file_contents;
	if (file.is_open()) {
		while (getline(file, text_line))
		{
			file_contents += text_line;
			file_contents.push_back('\n');
		}
	}
	else {
		cout << "Could not open file: " << file_name;
		exit(1);
	}
	return file_contents;
}

vector <string> parsePrograms(string program_text) {
	vector <string> programs;

	int prev_pos = 0;
	while (prev_pos < program_text.length() - 1) {
		int pos = program_text.find('$', prev_pos);
		if (pos == string::npos) {
			cout << "WARNING - EOP missing at EOF" << endl;
			cout << "WARNING - EOP auto added" << endl;
			program_text.append("$");
			pos = program_text.length() - 1;
		}
		string program = program_text.substr(prev_pos, pos - prev_pos);
		programs.push_back(program);
		prev_pos = pos + 1;		
	}

	return programs;
}


int main(int argc, char* argv[])
{
	string file_text;
	if (argc == 2) {
		file_text = readFile(argv[1]);
	}
	else {
		file_text = readFile("../Compiler/Test.txt");
	}
	vector <string> programs = parsePrograms(file_text);
	cout << "Number of programs found: " << programs.size() << endl;

	Lexer lexer;
	lexer.lex(programs);
}