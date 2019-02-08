#include <iostream>
#include <fstream>
#include <string>

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
		cout << file_contents;
	}
	else {
		cout << "Could not open file";
	}
	return file_contents;
}


int main()
{
	string file_text = readFile("../Compiler/Test.txt");
}