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

	current_tree_node = current_tree_node->children[0].get();
	analyze_block();
}

bool SemanticAnalyzer::analyze_block()
{
	std::cout << current_tree_node->children.size() << std::endl;

	if (current_tree_node->children.size() == 2) {
		return true;
	}

	if (current_tree_node->children.size() == 3) {
		//TODO create new table node
		current_tree_node = current_tree_node->children[1].get();

		return analyze_statement_list();
	}
	return false;
}

bool SemanticAnalyzer::analyze_statement_list()
{
	if (current_tree_node->children.size() != 0) {
		return analyze_statement() || analyze_statement_list();
	}
	return false;
}

bool SemanticAnalyzer::analyze_statement()
{
	if (current_tree_node->children.size() != 0) {

	}
	return false;
}
