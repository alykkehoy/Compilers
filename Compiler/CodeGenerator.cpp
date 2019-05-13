#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(/* args */)
{
}

CodeGenerator::~CodeGenerator()
{
}

void CodeGenerator::generate_code(Program& program)
{
	static_id = 0;
    this->current_program = &program;
    this->current_ast = &program.ast.head;
    this->current_scope = &program.scope_tree;

	current_ast = current_ast->children[0].get();
	gen_block();

	backpatch();

	for (int i = current_program->code.length(); i < 192; i++) {
		current_program->code += "0";
	}
}

//TODO
bool CodeGenerator::gen_block()
{
	//if (current_scope->parent != nullptr) {
	//	current_scope = current_scope->children
	//}

	for (int i = 0; i < current_ast->children.size(); i++) {
		switch (current_ast->children[i]->node_type)
		{
			//cases if, while, print
		case IF_STATEMENT:
			break;
		case WHILE_STATEMENT:
			break;
		case PRINT:
			current_ast = current_ast->children[i].get();
			gen_print();
			current_ast = current_ast->parent;
			break;
		case ASSIGNMENT_STATEMENT:
			current_ast = current_ast->children[i].get();
			gen_assignment();
			current_ast = current_ast->parent;
			break;
		case VAR_DECL:
			current_ast = current_ast->children[i].get();
			gen_var_decl();
			current_ast = current_ast->parent;
			break;
		default:
			break;
		}
	}

	return false;
}

//TODO print(1)
bool CodeGenerator::gen_print()
{
	if (current_ast->children.size() == 1) {
		auto scope_row = Tree::find_var(current_scope, current_ast->children[0]->token->text[0]);

		switch (scope_row->type)
		{
		case I_TYPE:
			gen_print_int();
			break;
		case S_TYPE:
			gen_print_string();
			break;
		case B_TYPE:
			gen_print_bool();
			break;
		default:
			break;
		}
	}

	return false;
}

//TODO
bool CodeGenerator::gen_print_int()
{
	current_program->code += "AC";

	//var loc
	auto row = find_static_row(current_ast->children[0]->token->text[0]);
	current_program->code += row->temp_loc;

	current_program->code += "A2";
	current_program->code += "01";
	current_program->code += "FF";

	return false;
}

//TODO
bool CodeGenerator::gen_print_string()
{
	return false;
}

//TODO
bool CodeGenerator::gen_print_bool()
{
	return false;
}

//TODO
bool CodeGenerator::gen_var_decl()
{
	switch (current_ast->children[0]->node_type)
	{
	case I_TYPE:
		gen_int();
		break;
	case S_TYPE:
		gen_string();
		break;
	case B_TYPE:
		gen_boolean();
		break;
	default:
		break;
	}
	return false;
}

//TODO
bool CodeGenerator::gen_int()
{
	std::shared_ptr<static_row> new_row(new static_row);
	new_row->var = current_ast->children[1]->token->text[0];
	new_row->temp_loc = "T" + std::to_string(static_id) + "XX";
	static_id++;

	current_program->code += "A9";
	current_program->code += "00";
	current_program->code += "8D";
	//temp location for var
	current_program->code += new_row->temp_loc;

	static_table.push_back(new_row);
	return false;
}

//TODO
bool CodeGenerator::gen_string()
{
	return false;
}

//TODO
bool CodeGenerator::gen_boolean()
{
	std::shared_ptr<static_row> new_row(new static_row);
	new_row->var = current_ast->children[1]->token->text[0];
	new_row->temp_loc = "T" + std::to_string(static_id) + "XX";
	static_id++;

	current_program->code += "A9";
	current_program->code += "00";
	current_program->code += "8D";
	//temp location for var
	current_program->code += new_row->temp_loc;

	static_table.push_back(new_row);
	return false;
}

//TODO look up type and go to that code gen function
bool CodeGenerator::gen_assignment()
{
	auto scope_row = Tree::find_var(current_scope, current_ast->children[0]->token->text[0]);

	switch (scope_row->type)
	{
	case I_TYPE:
		gen_assign_int();
		break;
	case S_TYPE:
		gen_assign_string();
		break;
	case B_TYPE:
		gen_assign_bool();
		break;
	default:
		break;
	}

	return false;
}

//TODO var loc
//TODO a = b, a + 1, 1 + 1, etc
bool CodeGenerator::gen_assign_int()
{
	//cout << Token::print_token_type(current_ast->children[1]->token->token_type) << endl;

	//a = 1
	if (current_ast->children.size() == 2 && current_ast->children[1]->token->token_type == DIGIT) {
		current_program->code += "A9";
		current_program->code += ("0" + current_ast->children[1]->token->text);
		current_program->code += "8D";

		auto row = find_static_row(current_ast->children[0]->token->text[0]);
		current_program->code += row->temp_loc;
	}
	//a = b
	else if (current_ast->children.size() == 2 && current_ast->children[1]->token->token_type == CHAR) {
		current_program->code += "AD";

		auto row = find_static_row(current_ast->children[1]->token->text[0]);
		current_program->code += row->temp_loc;

		current_program->code += "8D";

		row = find_static_row(current_ast->children[0]->token->text[0]);
		current_program->code += row->temp_loc;
	}
	return false;
}

//TODO
bool CodeGenerator::gen_assign_string()
{
	return false;
}

//TODO
bool CodeGenerator::gen_assign_bool()
{
	//a = true
	if (current_ast->children.size() == 2) {
		current_program->code += "A9";

		if (current_ast->children[1]->token->text[0] == 't') {
			current_program->code += "00";
		}
		else {
			current_program->code += "01";
		}

		current_program->code += "8D";
		auto row = find_static_row(current_ast->children[0]->token->text[0]);
		current_program->code += row->temp_loc;

	}
	return false;
}

//TODO
std::shared_ptr<static_row> CodeGenerator::find_static_row(char var)
{
	for (int i = 0; i < static_table.size(); i++) {
		if (static_table[i]->var == var) {
			return static_table[i];
		}
	}
	return nullptr;
}

bool CodeGenerator::backpatch()
{
	current_program->code += "00";


	for (int i = 0; i < static_table.size(); i++) {
		//calc real loc
		//stream.clear();
		//stream.flush();

		std::stringstream stream;
		stream << std::hex << (current_program->code.length() + 1) / 2;
		static_table[i]->loc = stream.str();

		static_table[i]->loc += "00";

		//backpatch
		for (int j = 0; j < current_program->code.size(); j++) {
			if (current_program->code[j] == 'T' && current_program->code[j + 1] == static_table[i]->temp_loc[1]) {
				current_program->code[j] = static_table[i]->loc[0];
				current_program->code[j + 1] = static_table[i]->loc[1];
				current_program->code[j + 2] = static_table[i]->loc[2];
				current_program->code[j + 3] = static_table[i]->loc[3];
			}
		}
		current_program->code += "AA";
	}
	return false;
}
