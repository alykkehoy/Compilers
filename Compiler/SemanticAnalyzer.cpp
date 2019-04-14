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
	current_scope_node = &program.scope_tree;

	current_ast_node->node_type = PROGRAM;
	current_cst_node = current_cst_node->children[0].get();
	analyze_block();
}

bool SemanticAnalyzer::analyze_block()
{
	//if nothing is in block dont do anything
	//if (current_cst_node->children.size() == 2) {
	//	return true;
	//}

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
	if (current_cst_node->children.size() == 0) {
		return true;
	}
	current_cst_node = current_cst_node->children[0].get();
	bool return_val = (analyze_statement() || analyze_statement_list());
	current_cst_node = current_cst_node->parent;
	return return_val;
}

bool SemanticAnalyzer::analyze_statement()
{
	bool return_val = false;
	if (current_cst_node->children.size() != 0) {
		current_cst_node = current_cst_node->children[0].get();
		switch (current_cst_node->node_type)
		{
		case PRINT_STATEMENT:
			return_val = analyze_print_statement();
			break;
		case ASSIGNMENT_STATEMENT:
			return_val = analyze_assignment_statement();
			break;
		case VAR_DECL:
			return_val = analyze_var_decl();
			break;
		case WHILE_STATEMENT:
			break;
		case IF_STATEMENT:
			break;
		case BLOCK:
			return_val = analyze_block();
			break;
		default:
			break;
		}
		current_cst_node = current_cst_node->parent;
	}
	return return_val;
}

bool SemanticAnalyzer::analyze_print_statement()
{
	return false;
}

bool SemanticAnalyzer::analyze_assignment_statement()
{
	current_ast_node = Tree::create_node(current_ast_node, ASSIGNMENT_STATEMENT);
	//TODO check if var is same as assignment
	auto scope_row = Tree::find_var(current_scope_node, current_cst_node->children[0]->token->text[0]);
	if (scope_row != nullptr) {
		Tree::create_node(current_ast_node, current_cst_node->children[0]->node_type, current_cst_node->children[0]->token);
		scope_row->initialized = true;
	}
	else {
		std::cout << "Error var not found" << std::endl;
		return false;
	}
	return false;
}

bool SemanticAnalyzer::analyze_var_decl()
{
	current_ast_node = Tree::create_node(current_ast_node, ASSIGNMENT_STATEMENT);
	auto found_scope = Tree::find_var(current_scope_node, current_cst_node->children[0]->token->text[0]);

	//TODO also if the scope is not the current scope
	if (found_scope == nullptr) {
		Tree::create_node(current_ast_node, current_cst_node->children[0]->node_type);

		std::shared_ptr<scope_row> row(new scope_row);
		row->token = current_cst_node->children[1]->token;

		current_scope_node->rows.push_back(row);
	}
	else {
		std::cout << "var already declared" << std::endl;
	}

	return false;
}
