#pragma once

#include "Program.h"
#include "Token.h"
#include "Tree.h"

struct static_row
{
	string temp_loc = "XXXX";
	char var;
	string loc;
};

class CodeGenerator
{
private:
    Program* current_program;
    tree_node* current_ast;
    scope* current_scope;
	int static_id;
	std::vector<std::shared_ptr<static_row>> static_table;

public:
    CodeGenerator(/* args */);
    ~CodeGenerator();

    void generate_code(Program& program);

	bool gen_block();
	bool gen_print();
	bool gen_print_int();
	bool gen_print_string();
	bool gen_print_bool();
	bool gen_var_decl();
	bool gen_int();
	bool gen_string();
	bool gen_boolean();
	bool gen_assignment();
	bool gen_assign_int();
	bool gen_assign_string();
	bool gen_assign_bool();

	std::shared_ptr<static_row> find_static_row(char var);
};
