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
	return false;
}
