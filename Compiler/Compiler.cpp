#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#include "Program.h"
#include "Parser.h"
#include "Token.h"
#include "Lexer.h"
#include "SemanticAnalyzer.h"

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

//takes a string of text from the file and splits it into separate stings for individual programs
//will also warn the user if there is no '$' found at the end of the file
vector <Program> parsePrograms(string program_text) {
	vector <Program> programs;

	int program_num = 1;
	int prev_pos = 0;
	while (prev_pos < program_text.length() - 1) {
		int pos = program_text.find('$', prev_pos);
		if (pos == string::npos) {
			cout << "WARNING - EOP missing at EOF" << endl;
			cout << "WARNING - EOP auto added" << endl;
			program_text.append("$");
			pos = program_text.length() - 1;
		}
		Program program(program_num, program_text.substr(prev_pos, pos - prev_pos));
		program_num++;

		programs.push_back(program);
		prev_pos = pos + 1;		
	}

	return programs;
}

//the compiler takes a file name as an argument
//if no file name if provide it uses the default Test.txt in the Compiler folder
int main(int argc, char* argv[])
{
	string file_text;
	if (argc == 2) {
		file_text = readFile(argv[1]);
	}
	else {
		file_text = readFile("../Compiler/Test.txt");
	}

	//after the file is read in the string is passed to parsePrograms
	//where it is split at '$' into individual strings representing the programs
	vector <Program> programs = parsePrograms(file_text);
	cout << "Number of programs found: " << programs.size() << endl;

	//the vector of program strings is passed into the lexer
	Lexer lexer(true);
	Parser parser(true);
	SemanticAnalyzer semantic_analyzer;

	for (int i = 0; i < programs.size(); i++) {
		lexer.lex(programs[i]);
		if (programs[i].passed_lex) {
			parser.parse(programs[i]);
		}
		//cout << programs[i].passed_parse << endl;
		if (programs[i].passed_parse) {
			cout << endl << "Program " << i + 1 << " CST:" << endl;
			programs[i].cst.print_tree();
			cout << endl;
		}
		if (programs[i].passed_parse) {
			semantic_analyzer.analyze(programs[i]);
		}
		cout << "--------------------------------------" << endl << endl;
	}
}