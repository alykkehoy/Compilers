#pragma once
#include "Program.h"
#include "Tree.h"

class SemanticAnalyzer
{
public:
	SemanticAnalyzer();
	~SemanticAnalyzer();

	void analyze(Program& program);

private:
	Program* current_program = nullptr;
	scope* current_scope_node;
	tree_node* current_cst_node;
	tree_node* current_ast_node;

	bool analyze_block();
	bool analyze_statement_list();
	bool analyze_statement();
	bool analyze_print_statement();
	bool analyze_assignment_statement();
	bool analyze_var_decl();
	//bool analyze_while_statement();
	//bool analyze_if_statement();
	//bool analyze_expr();
	//bool analyze_int_expr();
	//bool analyze_string_expr();
	//bool analyze_boolean_expr();
	//bool analyze_id();
	//bool analyze_char_list();
	//bool analyze_type();
	//bool analyze_char();
	//bool analyze_digit();
	//bool analyze_bool_op();
	//bool analyze_bool_val();
	//bool analyze_int_op();
};

