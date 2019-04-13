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
	current_tree_node = &program.cst.head;
	analyze_block();
}

bool SemanticAnalyzer::analyze_block()
{
	if (current_tree_node->children.size != 0) {
		current_tree_node = current_tree_node->children[1].get();
		//create new table node
	}
	return false;
}

bool SemanticAnalyzer::analyze_statement_list()
{
	if (current_tree_node->children.size != 0) {
		switch (current_tree_node->children[0]->node_type)
		{
		
		default:
			break;
		}
	}
	return false;
}
