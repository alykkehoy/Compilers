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
	std::vector<string> errors;
	std::vector<string> warnings;
	Program* current_program = nullptr;
	scope* current_scope_node;
	tree_node* current_cst_node;
	tree_node* current_ast_node;

	void print_errors();
	void print_warnings();

	bool analyze_block();
	bool analyze_statement_list();
	bool analyze_statement();
	bool analyze_print_statement();
	bool analyze_assignment_statement();
	bool analyze_var_decl();
	bool analyze_while_statement();
	bool analyze_if_statement();
	bool analyze_expr();
	bool analyze_int_expr();
	bool analyze_string_expr();
	bool analyze_boolean_expr();

	static bool type_check(const TokenType& var_type, const TokenType& expr_type);
	static bool type_check_helper(const TokenType& var_type, const TokenType& expr_type);

	void create_warnings(const scope* scope_table);
};

