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
		case IF_STATEMENT:
			break;
		case WHILE_STATEMENT:
			break;
		case PRINT:
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
	current_program->code += "XX";
	current_program->code += "XX";

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
	gen_assign_int();
	return false;
}

//TODO var loc
//TODO a + 1, 1 + 1, etc
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
