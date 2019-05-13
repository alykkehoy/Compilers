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
	current_program->code += "XX";
	current_program->code += "XX";

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
	//current_program->code += "XX";
	//current_program->code += "XX";

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
	if (current_ast->children.size() == 2) {
		current_program->code += "A9";
		current_program->code += ("0" + current_ast->children[1]->token->text);
		current_program->code += "8D";
		//var loc
		current_program->code += "XX";
		current_program->code += "XX";
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
	return false;
}

std::shared_ptr<static_row> CodeGenerator::find_static_row(char var)
{
	return std::shared_ptr<static_row>();
}
