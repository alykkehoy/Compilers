#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(/* args */)
{
}

CodeGenerator::~CodeGenerator()
{
}

void CodeGenerator::generate_code(Program& program)
{
    this->current_program = &program;
    this->current_ast = &program.ast.head;
    this->current_scope_tree = &program.scope_tree;

	current_ast = current_ast->children[0].get();
	gen_block();

	for (int i = current_program->code.length(); i < 192; i++) {
		current_program->code += "0";
	}
}

//TODO
bool CodeGenerator::gen_block()
{
	for (int i = 0; i < current_ast->children.size(); i++) {
		switch (current_ast->children[i]->node_type)
		{
			//cases if, while, print
		case ASSIGNMENT_STATEMENT:
			current_ast = current_ast->children[i].get();
			// gen assignment
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
	current_program->code += "A9";
	current_program->code += "00";
	current_program->code += "8D";
	//temp location for var
	current_program->code += "";
	current_program->code += "";

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

//TODO
bool CodeGenerator::gen_assignment()
{
	return false;
}

//TODO
bool CodeGenerator::gen_assign_int()
{
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
