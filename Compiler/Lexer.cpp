#include "Lexer.h"

Lexer::Lexer()
{
	init_map();
}

Lexer::Lexer(bool print)
{
	init_map();
	this->print = print;
}

Lexer::~Lexer()
{
}

void Lexer::init_map()
{
	token_map = {
		{"}", R_BRACE},
		{"{", L_BRACE},
		{")", R_BOOL_EXP},
		{"(", L_BOOL_EXP},
		{"while", WHILE},
		{"if", IF},
		{"string", S_TYPE},
		{"int", I_TYPE},
		{"boolean", B_TYPE},
		{"=", ASSIGN_OP},
		{"print", PRINT},
		{"true", BOOL},
		{"false",BOOL},
		{"==", BOOL_OP},
		{"!=", BOOL_OP},
		{"+", ADD},
		{"$", EOP}
	};

	for (int i = 'a'; i <= 'z'; i++) {
		string s(1, i);
		token_map.insert(pair<string, TokenType>(s, CHAR));
	}
	for (int i = '0'; i <= '9'; i++) {
		string s(1, i);
		token_map.insert(pair<string, TokenType>(s, DIGIT));
	}
};


void Lexer::lex(vector<Program>& programs)
{
	for (int i = 0; i < programs.size(); i++) {
		//cout << "INFO Lexer - lexing program " << programs[i].program_num << endl;
		lex(programs[i]);
	}
	return;
}

void Lexer::lex(Program& program) {
	cout << "INFO Lexer - lexing program " << program.program_num << endl;
	remove_comments(program.program_text);
	
	create_tokens(program);
	validate_tokens(program);
	return;
}

void Lexer::create_tokens(Program& program)
{
	string& program_text = program.program_text;

	vector<Token>& unvalidated_tokens = program.tokens;
	vector<string> words;
	int line_num = 0;
	int line_start = 0;

	for (int i = 0; i < program_text.length(); i++) {
		if (program_text[i] == '\n') {
			line_num++;
			line_start = i + 1;
		}
		//checking for { or }
		else if (is_bracket(program_text[i])) {
			unvalidated_tokens.push_back(create_bracket_token(program_text[i], line_num, i - line_start));
		}
		//checking for ( or )
		else if (is_boolean_expression(program_text[i])) {
			unvalidated_tokens.push_back(create_boolean_expression_token(program_text[i], line_num, i - line_start));
		}
		//checking for strings by looking for "
		else if (is_string_expression(program_text[i])) {
			Token token;
			token.position.first = line_num;
			token.position.second = i - line_start;

			pair<bool, int> result = find_string_end(program_text, i);
			token.text = program_text.substr(i, result.second - i);
			if (result.first) {
				token.token_type = STRING_EXP;
			}
			i = result.second - 1;
			unvalidated_tokens.push_back(token);
		}
		//checking for = or == or !=
		else if (program_text[i] == '=' || (program_text[i] == '!' && program_text[i+1] == '=')) {
			Token token;
			token.position.first = line_num;
			token.position.second = i - line_start;
			if (program_text[i + 1] == '=') {
				token.text = program_text.substr(i, 2);
				token.token_type = BOOL_OP;
				i = i + 1;
			}
			else {
				token.text = '=';
				token.token_type = ASSIGN_OP;
			}
			unvalidated_tokens.push_back(token);
		}
		else if (program_text[i] == '+') {
			Token token;
			token.position.first = line_num;
			token.position.second = i - line_start;
			token.text = "+";
			token.token_type = ADD;

			unvalidated_tokens.push_back(token);
		}
		//everything else thats not a space or tab
		else if (program_text[i] != ' ' && program_text[i] != '\t') {
			int end = i + 1;
			//find the end of the curent word by continuing untill finding a delimiter
			while (end < program_text.length()) {
				if (is_delimiter(program_text, end)) {
					Token token;
					token.position.first = line_num;
					token.position.second = i - line_start;
					token.text = program_text.substr(i, end - i);

					unvalidated_tokens.push_back(token);
					i = end - 1;
					break;
				}
				end++;
			}
			if (end == program_text.length()) {
				Token token;
				token.position.first = line_num;
				token.position.second = i - line_start;
				token.text = program_text.substr(i, end - 1);
				i = end;
			}
		}
	}

	return;
}

bool Lexer::is_delimiter(string& program_text, int pos)
{
	return (is_bracket(program_text[pos])
		|| is_boolean_expression(program_text[pos])
		|| program_text[pos] == '\n'
		|| program_text[pos] == ' '
		|| program_text[pos] == '\t'
		|| program_text[pos] == '='
		|| program_text[pos] == '!'
		|| program_text[pos] == '+');
}

void Lexer::validate_tokens(Program& program)
{
	vector<Token>& unvalidated_tokens = program.tokens;
	int errors = 0;
	vector<string> error_text;

	//go through all the tokens
	//if the token was not already found (aka not NONE) try to find the token in the map
	//if its not found in the map its not in the grammer and is an error
	//if it is found update its token type
	for (int i = 0; i < unvalidated_tokens.size(); i++) {
		if (unvalidated_tokens[i].token_type == NONE) {
			if (token_map.find(unvalidated_tokens[i].text) == token_map.end()) {
				error_text.push_back("ERROR Lexer - Error (" + to_string(unvalidated_tokens[i].position.first)
					+ ":" + to_string(unvalidated_tokens[i].position.second) + ") unrecognized token: "
					+ unvalidated_tokens[i].text);
				errors++;
				unvalidated_tokens[i].token_type = NONE;
			}
			else {
				unvalidated_tokens[i].token_type = token_map.find(unvalidated_tokens[i].text)->second;
			}
		}
	}

	//print out found tokens if verbose print is on (defualt true)
	if (print) {
		verbose_print(unvalidated_tokens);
	}

	//if any lexing errors were found print them out as a list
	if (errors > 0) {
		cout << "INFO Lexer - Lex failed with " << errors << " errors" << endl << endl;
		cout << "ERROR LIST:" << endl;
		for (int i = 0; i < error_text.size(); i++) {
			cout << error_text[i] << endl;
		}
		return;
	}

	//if there were no lexing errors found a notification is given
	program.passed_lex = true;
	cout << "INFO Lexer - Lex complete with 0 errors" << endl;
	return;
}

void Lexer::verbose_print(vector<Token> tokens)
{
	for (int i = 0; i < tokens.size(); i++) {
		switch (tokens[i].token_type)
		{
		case R_BRACE:
			cout << "DEBUG Lexer - R_Brace [ } ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case L_BRACE:
			cout << "DEBUG Lexer - L_Brace [ { ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case R_BOOL_EXP:
			cout << "DEBUG Lexer - Brace [ ) ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case L_BOOL_EXP:
			cout << "DEBUG Lexer - Brace [ ( ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case WHILE:
			cout << "DEBUG Lexer - While [ while ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case IF:
			cout << "DEBUG Lexer - If [ if ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case S_TYPE:
			cout << "DEBUG Lexer - Type [ string ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case I_TYPE:
			cout << "DEBUG Lexer - Type [ int ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case B_TYPE:
			cout << "DEBUG Lexer - Type [ boolean ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case ASSIGN_OP:
			cout << "DEBUG Lexer - Assign Operator [ = ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case PRINT:
			cout << "DEBUG Lexer - Print [ print ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case BOOL:
			cout << "DEBUG Lexer - Boolean [ " << tokens[i].text << " ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case BOOL_OP:
			cout << "DEBUG Lexer - Boolean Operator [ " << tokens[i].text << " ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case ADD:
			cout << "DEBUG Lexer - Add [ + ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case CHAR:
			cout << "DEBUG Lexer - Char [ " << tokens[i].text << " ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case DIGIT:
			cout << "DEBUG Lexer - Digit [ " << tokens[i].text << " ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case STRING_EXP:
			cout << "DEBUG Lexer - String Expression [ " << tokens[i].text << " ] found at (" << tokens[i].position.first << ":" << tokens[i].position.second << ")" << endl;
			break;
		case NONE:
			cout << "ERROR Lexer - Error (" << tokens[i].position.first << ":" << tokens[i].position.second << ") unrecognized token: " << tokens[i].text << endl;
			break;
		default:
			cout << "PRINT ERROR - TOKEN HAS INVALID TOKEN TYPE ENUM" << endl;
			break;
		}
	}	
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
}

bool Lexer::is_bracket(char character)
{
	return (character == '{' || character == '}');
}

Token Lexer::create_bracket_token(char character, int line_num, int pos)
{
	Token token;
	token.position.first = line_num;
	token.position.second = pos;
	if (character == '{') {
		token.text = "{";
		token.token_type = L_BRACE;
	}
	else {
		token.text = "}";
		token.token_type = R_BRACE;
	}
	return token;
}

bool Lexer::is_boolean_expression(char character)
{
	return (character == '(' || character == ')');
}

Token Lexer::create_boolean_expression_token(char character, int line_num, int pos)
{
	Token token;
	token.position.first = line_num;
	token.position.second = pos;

	if (character == '(') {
		token.text = "(";
		token.token_type = L_BOOL_EXP;
	}
	else {
		token.text = ")";
		token.token_type = R_BOOL_EXP;
	}

	return token;
}

bool Lexer::is_string_expression(char character)
{
	return (character == '"');
}

pair<bool, int> Lexer::find_string_end(string program_text, int pos)
{
	pair<bool, int> result;
	result.first = true;
	int end = pos + 1;
	result.second = end + 1;
	while (end < program_text.length() & program_text[end] != '"') {
		if ((!islower(program_text[end]) || !isalpha(program_text[end])) & program_text[end] != ' ') {
			result.first = false;
		}
		end++;
		result.second = end + 1;
	}
	if (end == program_text.length()) {
		cout << "WARNING Lexer - No end of string expression found" << endl;
	}
	return result;
}
