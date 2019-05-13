#pragma once

#include "Program.h"
#include "Token.h"
#include "Tree.h"

class CodeGenerator
{
private:
    Program* current_program;
    tree_node* current_ast;
    scope* current_scope_tree;

public:
    CodeGenerator(/* args */);
    ~CodeGenerator();

    void generate_code(Program& program);

	bool gen_block();
	//bool parse_statement_list();
	//bool parse_statement();
	//bool parse_print_statement();
	//bool parse_assignment_statement();
	bool gen_var_decl();
	bool gen_int();
	bool gen_string();
	bool gen_boolean();
	bool gen_assignment();
	bool gen_assign_int();
	bool gen_assign_string();
	bool gen_assign_bool();
	//bool parse_while_statement();
	//bool parse_if_statement();
	//bool parse_expr();
	//bool parse_int_expr();
	//bool parse_string_expr();
	//bool parse_boolean_expr();
	//bool parse_id();
	//bool parse_char_list();
	//bool parse_type();
	//bool parse_char();
	//bool parse_digit();
	//bool parse_bool_op();
	//bool parse_bool_val();
	//bool parse_int_op();

};
