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
		//cout << file_contents;
	}
	else {
		cout << "Could not open file";
	}
	return file_contents;
}

vector <string> parsePrograms(string program_text) {
	vector <string> programs;

	int prev_pos = 0;
	while (program_text.find('$', prev_pos) != string::npos) {
		int pos = program_text.find('$', prev_pos);
		string program = program_text.substr(prev_pos, pos - prev_pos);
		programs.push_back(program);
		prev_pos = pos + 1;
		
		//cout << program << endl;
	}

	return programs;
}


int main()
{
	string file_text = readFile("../Compiler/Test.txt");
	vector <string> programs = parsePrograms(file_text);
	cout << "Number of programs found: " << programs.size() << endl;

	Lexer lexer;
	while (!programs.empty()) {
		lexer.lex(programs.front());
		programs.erase(programs.begin());
	}
}