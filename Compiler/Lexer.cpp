#include "Lexer.h"

Lexer::Lexer()
{
	init_map();
}


Lexer::~Lexer()
{
}

void Lexer::init_map()
{

		//BOOL,
		//BOOL_OP,
		//STRING_EXP,
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
		token_map.insert(pair<string, TokenType>( s, CHAR));
	}
	for (int i = '0'; i <= '9'; i++) {
		string s(1, i);
		token_map.insert(pair<string, TokenType>(s, DIGIT));
	}
};


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

vector<Token> Lexer::create_tokens(string program_text)
{
	vector<Token> unvalidated_tokens;
	vector<string> words;
	int line_num = 0;

	for (int i = 0; i < program_text.length(); i++) {
		if (program_text[i] == '\n') {
			line_num++;
		}
		else if (is_bracket(program_text[i])) {
			unvalidated_tokens.push_back(create_bracket_token(program_text[i], line_num, i));
			//cout << "b1" << endl;
		}
		else if (is_boolean_expression(program_text[i])) {
			//cout << "b2" << endl;
			unvalidated_tokens.push_back(create_boolean_expression_token(program_text[i], line_num, i));
		}
		else if (false) {
			//TO HANDLE COMMENTS
		}
		else if (program_text[i] != ' ' && program_text[i] != '\t') {
			int end = i;
			while (end < program_text.length()) {
				if (is_bracket(program_text[end])
					|| is_boolean_expression(program_text[end])
					|| program_text[end] == '\n'
					|| program_text[end] == ' '
					|| program_text[end] == '\t') {

					//cout << 1 << program_text.substr(i, end - i) << endl;
					Token token;
					token.position.first = line_num;
					token.position.second = i;
					token.text = program_text.substr(i, end - i);

					unvalidated_tokens.push_back(token);
					i = end - 1;
					break;
				}
				end++;
			}
			if (end == program_text.length()) {
				//cout << 2 << program_text.substr(i, end - i) << endl;
				Token token;
				token.position.first = line_num;
				token.position.second = i;
				token.text = program_text.substr(i, end - 1);
				i = end;
			}
		}
	}

	//for (int i = 0; i < unvalidated_tokens.size(); i++) {
	//	cout << i << unvalidated_tokens[i].text << endl;
	//}

	return unvalidated_tokens;
}

vector<Token> Lexer::validate_tokens(vector<Token> unvalidated_tokens)
{
	int errors = 0;
	vector<Token> validated_tokens;
	vector<string> error_text;

	for (int i = 0; i < unvalidated_tokens.size(); i++) {
		if (token_map.find(unvalidated_tokens[i].text) == token_map.end()) {
			cout << "ERROR Lexer - Error (" + to_string(unvalidated_tokens[i].position.first)
				+ ":" + to_string(unvalidated_tokens[i].position.second) + ") unrecognized token: "
				+ unvalidated_tokens[i].text << endl;
			errors++;

			unvalidated_tokens[i].token_type = NONE;
		}
		else {
			unvalidated_tokens[i].token_type = token_map.find(unvalidated_tokens[i].text)->second;
		}

		//if (unvalidated_tokens[i].token_type != NONE) {
		//	validated_tokens.push_back(unvalidated_tokens[i]);
		//}
		//else {

		//}
	}

	for (int i = 0; i < validated_tokens.size(); i++) {
	cout << i << " : " << validated_tokens[i].token_type << endl;
	}

	return validated_tokens;
}



bool Lexer::lex_single(string program_text) {
	int errors = 0;
	int line_num = 0;
	list <Token> program_tokens;
	vector <string> error_text;

	vector<Token> unvalidated_tokens = create_tokens(program_text);
	vector<Token> validated_tokens = validate_tokens(unvalidated_tokens);

	//first we strip comments from the program text string
	//remove_comments(program_text);

	//then we loop through the text searching for possible tokens till reaching the end of the string
	//for (int i = 0; i < program_text.length(); i++) {
	//	if (program_text[i] == '\n') {
	//		line_num++;
	//	}
	//	else if (is_bracket(program_text[i])) {
	//		program_tokens.push_back(create_bracket_token(program_text[i], line_num, i));
	//		cout << "DEBUG Lexer - Brace [ " << program_text[i] << " ] found at (" << line_num << ":" << i << ")" << endl;
	//	}
	//	else if (is_operator(program_text[i])) {
	//		program_tokens.push_back(create_operator_token(program_text[i], line_num, i));
	//		cout << "DEBUG Lexer - Operator [ " << program_text[i] << " ] found at (" << line_num << ":" << i << ")" << endl;
	//	}
	//	else if (is_print(program_text, i)) {
	//		program_tokens.push_back(create_print_token(line_num, i));
	//		cout << "DEBUG Lexer - Print [ print ] found at (" << line_num << ":" << i << ")" << endl;
	//		i = i + 4;
	//	}
	//	else if (is_while(program_text, i)) {
	//		program_tokens.push_back(create_while_token(line_num, i));
	//		cout << "DEBUG Lexer - While [ while ] found at (" << line_num << ":" << i << ")" << endl;
	//		i = i + 4;
	//	}
	//	else if (is_if(program_text, i)) {
	//		program_tokens.push_back(create_if_token(line_num, i));
	//		cout << "DEBUG Lexer - If [ if ] found at (" << line_num << ":" << i << ")" << endl;
	//		i = i + 1;
	//	}
	//	else if (is_int(program_text, i)) {
	//		program_tokens.push_back(create_int_token(line_num, i));
	//		cout << "DEBUG Lexer - Type [ int ] found at (" << line_num << ":" << i << ")" << endl;
	//		i = i + 2;
	//	}
	//	else if (is_string(program_text, i)) {
	//		program_tokens.push_back(create_string_token(line_num, i));
	//		cout << "DEBUG Lexer - Type [ string ] found at (" << line_num << ":" << i << ")" << endl;
	//		i = i + 5;
	//	}
	//	else if (is_boolean(program_text, i)) {
	//		program_tokens.push_back(create_boolean_token(line_num, i));
	//		cout << "DEBUG Lexer - Type [ boolean ] found at (" << line_num << ":" << i << ")" << endl;
	//		i = i + 6;
	//	}
	//	else if (is_boolean_value(program_text, i)) {
	//		program_tokens.push_back(create_boolean_value_token(program_text[i], line_num, i));
	//		if (program_text[i] == 't') {
	//			cout << "DEBUG Lexer - BOOLVAL [ true ] found at (" << line_num << ":" << i << ")" << endl;
	//			i = i + 3;
	//		}
	//		else {
	//			cout << "DEBUG Lexer - BOOLVAL [ false ] found at (" << line_num << ":" << i << ")" << endl;
	//			i = i + 4;
	//		}
	//	}
	//	else if (is_boolean_operation(program_text, i)) {
	//		program_tokens.push_back(create_boolean_operation_token(program_text[i], line_num, i));
	//		cout << "DEBUG Lexer - BOOLOP [ " << program_text.substr(i, 2) << " ] found at (" << line_num << ":" << i << ")" << endl;
	//		i = i + 1;
	//	}
	//	else if (is_assignment(program_text, i)) {
	//		program_tokens.push_back(create_assignment_token(line_num, i));
	//		cout << "DEBUG Lexer - ASSIGN_OP [ = ] found at (" << line_num << ":" << i << ")" << endl;
	//	}
	//	else if (is_boolean_expression(program_text[i])) {
	//		program_tokens.push_back(create_boolean_expression_token(program_text[i], line_num, i));
	//		cout << "DEBUG Lexer - BOOL_EXP [ " << program_text[i] << " ] found at (" << line_num << ":" << i << ")" << endl;
	//	}
	//	else if (is_string_expression(program_text[i])) {
	//		pair<bool, int> result = find_string_end(program_text, i);
	//		if (!result.first) {
	//			error_text.push_back("ERROR Lexer - Invalid string expression " + program_text.substr(i, result.second - i));
	//			cout << error_text.back() << endl;
	//			errors++;
	//		}
	//		else {
	//			program_tokens.push_back(create_string_expression_token(program_text.substr(i, result.second - i), line_num, i));
	//			cout << "DEBUG Lexer - STRING_EXP [ " << program_text.substr(i, result.second - i) << " ] found at (" << line_num << ":" << i << ")" << endl;
	//		}
	//		i = result.second - 1;
	//	}
	//	else if (is_digit(program_text, i)) {
	//		program_tokens.push_back(create_digit_token(program_text[i], line_num, i));
	//		cout << "DEBUG Lexer - Digit [ " << program_text[i] << " ] found at (" << line_num << ":" << i << ")" << endl;
	//	}
	//	else if (is_char(program_text, i)) {
	//		program_tokens.push_back(create_char_token(program_text[i], line_num, i));
	//		cout << "DEBUG Lexer - Char [ " << program_text[i] << " ] found at (" << line_num << ":" << i << ")" << endl;
	//	}
	//	//this serves as a catch all for the remaining text that is not a token
	//	else if (program_text[i] != ' ' && program_text[i] != '\t'){
	//		int end = i;
	//		while (end < program_text.length()) {
	//			if (is_bracket(program_text[end])
	//				|| is_boolean_expression(program_text[end])
	//				|| program_text[end] == '\n'
	//				|| program_text[end] == ' ') {
	//				error_text.push_back("ERROR Lexer - Error (" + to_string(line_num)
	//					 + ":" + to_string(i) + ") unrecognized token: " + program_text.substr(i, end - i));
	//				cout << error_text.back() << endl;
	//				i = end - 1;
	//				break;
	//			}
	//			end++;
	//		}
	//		errors++;
	//	}
	//}



	//if there are any errors the lexer will fail and print out the errors it caught
	//if (errors > 0) {
	//	cout << "INFO Lexer - Lex failed with " << errors << " errors" << endl << endl;
	//	cout << "ERROR LIST:" << endl;
	//	for (int i = 0; i < error_text.size(); i++) {
	//		cout << error_text[i] << endl;
	//	}
	//	cout << "--------------------------------------" << endl << endl;
	//	return false;
	//}

	////if there were no lexing errors found a notification is given
	////and all of our tokens from this program are added to the vector of all the tokens from all the programs
	//cout << "INFO Lexer - Lex complete with 0 errors" << endl;
	//cout << "--------------------------------------" << endl << endl;
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

bool Lexer::is_operator(char character)
{
	return (character == '+');
}

Token Lexer::create_operator_token(char character, int line_num, int pos)
{
	Token token(ADD);
	token.position.first = line_num;
	token.position.second = pos;
	return token;
}

bool Lexer::is_char(string program_text, int pos)
{
	return (isalpha(program_text[pos]) && islower(program_text[pos]) && !isalnum(program_text[pos + 1]));
}

Token Lexer::create_char_token(char character, int line_num, int pos)
{
	Token token(CHAR);
	token.position.first = line_num;
	token.position.second = pos;
	token.character = character;
	return token;
}

bool Lexer::is_digit(string program_text, int pos)
{
	return (isdigit(program_text[pos]) && !isalnum(program_text[pos + 1]));
}

Token Lexer::create_digit_token(char character, int line_num, int pos)
{
	Token token(DIGIT);
	token.position.first = line_num;
	token.position.second = pos;
	token.digit = (int)character - 48;
	return token;
}

bool Lexer::is_print(string program_text, int pos)
{
	return (program_text.compare(pos, 5, "print") == 0);
}

Token Lexer::create_print_token(int line_num, int pos)
{
	Token token(PRINT);
	token.position.first = line_num;
	token.position.second = pos;
	return token;
}

bool Lexer::is_while(string program_text, int pos)
{
	return (program_text.compare(pos, 5, "while") == 0);
}

Token Lexer::create_while_token(int line_num, int pos)
{
	Token token(WHILE);
	token.position.first = line_num;
	token.position.second = pos;
	return token;
}

bool Lexer::is_if(string program_text, int pos)
{
	return (program_text.compare(pos, 2, "if") == 0);
}

Token Lexer::create_if_token(int line_num, int pos)
{
	Token token(IF);
	token.position.first = line_num;
	token.position.second = pos;
	return token;
}

bool Lexer::is_int(string program_text, int pos)
{
	return (program_text.compare(pos, 3, "int") == 0);
}

Token Lexer::create_int_token(int line_num, int pos)
{
	Token token(I_TYPE);
	token.position.first = line_num;
	token.position.second = pos;
	return token;
}

bool Lexer::is_string(string program_text, int pos)
{
	return (program_text.compare(pos, 6, "string") == 0);
}

Token Lexer::create_string_token(int line_num, int pos)
{
	Token token(S_TYPE);
	token.position.first = line_num;
	token.position.second = pos;
	return token;
}

bool Lexer::is_boolean(string program_text, int pos)
{
	return (program_text.compare(pos, 7, "boolean") == 0);
}

Token Lexer::create_boolean_token(int line_num, int pos)
{
	Token token(B_TYPE);
	token.position.first = line_num;
	token.position.second = pos;
	return token;
}

bool Lexer::is_boolean_value(string program_text, int pos)
{
	if (program_text.compare(pos, 4, "true") == 0) {
		return true;
	}
	else if (program_text.compare(pos, 5, "false") == 0) {
		return true;
	}
	return false;
}

Token Lexer::create_boolean_value_token(char character, int line_num, int pos)
{
	Token token(BOOL);
	token.position.first = line_num;
	token.position.second = pos;

	if (character == 't') {
		token.boolean = true;
	}
	else {
		token.boolean = false;
	}

	return token;
}

bool Lexer::is_boolean_operation(string program_text, int pos)
{
	if (program_text.compare(pos, 2, "==") == 0) {
		return true;
	}
	else if (program_text.compare(pos, 2, "!=") == 0) {
		return true;
	}
	return false;
}

Token Lexer::create_boolean_operation_token(char character, int line_num, int pos)
{
	Token token(BOOL_OP);
	token.position.first = line_num;
	token.position.second = pos;

	if (character == '=') {
		token.boolean = true;
	}
	else {
		token.boolean = false;
	}
	return token;
}

bool Lexer::is_assignment(string program_text, int pos)
{
	return (program_text[pos] == '=' && program_text[pos + 1] != '=');
}

Token Lexer::create_assignment_token(int line_num, int pos)
{
	Token token(ASSIGN_OP);
	token.position.first = line_num;
	token.position.second = pos;
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

Token Lexer::create_string_expression_token(string text, int line_num, int pos)
{
	Token token(STRING_EXP);
	token.position.first = line_num;
	token.position.second = pos;
	token.text = text;
	return token;
}
