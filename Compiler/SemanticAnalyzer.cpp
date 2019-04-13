#include "SemanticAnalyzer.h"



SemanticAnalyzer::SemanticAnalyzer()
{
}


SemanticAnalyzer::~SemanticAnalyzer()
{
}

void SemanticAnalyzer::analyze(Program& program)
{
	current_program = &program;
	current_ast_node = &program.ast.head;
	current_cst_node = &program.cst.head;

	current_ast_node->node_type = PROGRAM;
	current_cst_node = current_cst_node->children[0].get();
	analyze_block();
}

bool SemanticAnalyzer::analyze_block()
{
	//if nothing is in block dont do anything
	if (current_cst_node->children.size() == 2) {
		return true;
	}

	if (current_cst_node->children.size() == 3) {
		//TODO create new table node

		current_ast_node = Tree::create_node(current_ast_node, BLOCK);
		current_cst_node = current_cst_node->children[1].get();

		bool return_val = analyze_statement_list();

		current_ast_node = current_ast_node->parent;
		current_cst_node = current_cst_node->parent;

		return return_val;
	}
	return false;
}

bool SemanticAnalyzer::analyze_statement_list()
{
	if (current_cst_node->children.size() != 0) {
		//return analyze_statement() || analyze_statement_list();
	}
	return false;
}

bool SemanticAnalyzer::analyze_statement()
{
	if (current_cst_node->children.size() != 0) {

	}
	return false;
}
