#include "SemanticAnalyzer.h"



SemanticAnalyzer::SemanticAnalyzer()
{
}


SemanticAnalyzer::~SemanticAnalyzer()
{
}

void SemanticAnalyzer::analyze(Program& program)
{
	errors.clear();
	warnings.clear();

	current_program = &program;
	current_ast_node = &program.ast.head;
	current_cst_node = &program.cst.head;
	current_scope_node = &program.scope_tree;

	current_ast_node->node_type = PROGRAM;
	current_cst_node = current_cst_node->children[0].get();

	if (analyze_block()){
		current_program->passes_semantic_analysis = true;
	}

	std::cout << "\nSemantic Analysis:" << std::endl;
	print_errors();
	print_warnings();

}

void SemanticAnalyzer::print_errors()
{
	if (errors.size() != 0) {
		std::cout << "Failed with " << errors.size() << " Errors:" << std::endl;
		for (int i = 0; i < errors.size(); i++) {
			std::cout << errors[i] << std::endl;
		}
	}
	else {
		std::cout << "Complete with 0 Errors" << std::endl;
	}
}

void SemanticAnalyzer::print_warnings()
{
	if (warnings.size() != 0) {
		std::cout << "Complete with " << warnings.size() << " Warnings:" << std::endl;
		for (int i = 0; i < warnings.size(); i++) {
			std::cout << warnings[i] << std::endl;
		}
	}
	else {
		std::cout << "Complete with 0 Warnings" << std::endl;
	}
}

bool SemanticAnalyzer::analyze_block()
{
	if (current_cst_node->parent->parent != nullptr) {
		std::shared_ptr<scope> new_scope(new scope);
		new_scope->parent = current_scope_node;
		current_scope_node->children.push_back(new_scope);
		current_scope_node = new_scope.get();
	}

	current_ast_node = Tree::create_node(current_ast_node, BLOCK);
	current_cst_node = current_cst_node->children[1].get();

	bool return_val = analyze_statement_list();

	current_ast_node = current_ast_node->parent;
	current_cst_node = current_cst_node->parent;

	if (current_scope_node->parent != nullptr) {
		current_scope_node = current_scope_node->parent;
	}

	return return_val;
}

bool SemanticAnalyzer::analyze_statement_list()
{

	if (current_cst_node->children.size() == 0) {
		return true;
	}
	current_cst_node = current_cst_node->children[0].get();

	bool return_val = true;
	return_val = analyze_statement();
	current_cst_node = current_cst_node->parent->children[1].get();

	return_val = (return_val && analyze_statement_list());
	current_cst_node = current_cst_node->parent;
	return return_val;
}

bool SemanticAnalyzer::analyze_statement()
{
	bool return_val = false;
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
		return_val = analyze_while_statement();
		break;
	case IF_STATEMENT:
		return_val = analyze_if_statement();
		break;
	case BLOCK:
		return_val = analyze_block();
		break;
	default:
		break;
	}

	current_cst_node = current_cst_node->parent;
	return return_val;
}

//TODO test print (a)
bool SemanticAnalyzer::analyze_print_statement()
{
	bool return_val = false;
	
	current_ast_node = Tree::create_node(current_ast_node, PRINT);

	current_cst_node = current_cst_node->children[2].get();
	return_val = analyze_expr();

	current_cst_node = current_cst_node->parent;
	current_ast_node = current_ast_node->parent;
	
	return return_val;
}

//TODO ast node for assigned xpr
bool SemanticAnalyzer::analyze_assignment_statement()
{
	bool return_val = false;
	current_ast_node = Tree::create_node(current_ast_node, ASSIGNMENT_STATEMENT);

	auto scope_row = Tree::find_var(current_scope_node, current_cst_node->children[0]->token->text[0]);

	//if the var exists in the scope table, create node in ast and check type 
	if (scope_row != nullptr) {
		Tree::create_node(current_ast_node, current_cst_node->children[0]->node_type, current_cst_node->children[0]->token);

		current_cst_node = current_cst_node->children[2].get();
		TokenType check_against = current_cst_node->children[0]->node_type;

		//if the expr is a variable find its type
		if (current_cst_node->children[0]->node_type == CHAR) {
			auto found_scope = Tree::find_var(current_scope_node, current_cst_node->children[0]->token->text[0]);
			check_against = found_scope->type;
		}

		if (type_check(scope_row->type, check_against)) {
			return_val = analyze_expr();
			scope_row->initialized = true;
		}
		else {
			errors.push_back("ERROR Semantic Analysis - Assignment - Variable ("+ current_cst_node->parent->children[0]->token->text +") of type: "
			+ Token::print_token_type(scope_row->type) + " not: " + Token::print_token_type(check_against));

			errors.push_back("error wrong type");
		}
		current_cst_node = current_cst_node->parent;
	}
	else {
		errors.push_back("ERROR Semantic Analysis - Assignment - Variable (" + current_cst_node->children[0]->token->text + ") not declared");
	}
	current_ast_node = current_ast_node->parent;
	return return_val;
}

//TODO
bool SemanticAnalyzer::analyze_var_decl()
{
	bool return_val = false;
	current_ast_node = Tree::create_node(current_ast_node, VAR_DECL);
	auto found_scope = Tree::find_var(current_scope_node, current_cst_node->children[1]->token->text[0]);

	//TODO also if the scope is not the current scope
	if (found_scope == nullptr) {
		Tree::create_node(current_ast_node, current_cst_node->children[0]->node_type);
		Tree::create_node(current_ast_node, current_cst_node->children[1]->node_type, current_cst_node->children[1]->token);

		std::shared_ptr<scope_row> row(new scope_row);

		row->token = current_cst_node->children[1]->token;
		row->type = current_cst_node->children[0]->node_type;

		current_scope_node->rows.push_back(row);
		return_val = true;
	}
	else {
		errors.push_back("ERROR Semantic Analysis - Variable Declaration - Variable (" + found_scope->token->text + ") already declared");
	}
	current_ast_node = current_ast_node->parent;
	return return_val;
}

//TODO test
bool SemanticAnalyzer::analyze_while_statement()
{
	bool return_val = false;
	current_ast_node = Tree::create_node(current_ast_node, WHILE_STATEMENT);

	current_cst_node = current_cst_node->children[1].get();
	return_val = analyze_boolean_expr();
	current_cst_node = current_cst_node->parent;

	current_cst_node = current_cst_node->children[2].get();
	return_val = return_val && analyze_block();
	current_cst_node = current_cst_node->parent;

	return return_val;
}

//TODO test
bool SemanticAnalyzer::analyze_if_statement()
{
	bool return_val = false;
	current_ast_node = Tree::create_node(current_ast_node, IF_STATEMENT);

	current_cst_node = current_cst_node->children[1].get();
	return_val = analyze_boolean_expr();
	current_cst_node = current_cst_node->parent;

	current_cst_node = current_cst_node->children[2].get();
	return_val = return_val && analyze_block();
	current_cst_node = current_cst_node->parent;

	return return_val;
}

//TODO if char add node to ast
//test: print(a)
bool SemanticAnalyzer::analyze_expr()
{
	bool return_val = false;
	current_cst_node = current_cst_node->children[0].get();

	//TODO check if in scope
	if (current_cst_node->node_type == CHAR) {
		Tree::create_node(current_ast_node, current_cst_node->node_type, current_cst_node->token);

		auto found_scope = Tree::find_var(current_scope_node, current_cst_node->token->text[0]);

		if (found_scope == nullptr) {
			errors.push_back("ERROR Semantic Analysis - Expr - Variable (" + current_cst_node->token->text + ") not declared");
			current_cst_node = current_cst_node->parent;
			return false;
		}
		if (!found_scope->initialized) {
			errors.push_back("ERROR Semantic Analysis - Expr - Variable (" + current_cst_node->token->text + ") declared but not initialized");
			current_cst_node = current_cst_node->parent;
			return false;
		}

		found_scope->used = true;
		return_val = true;
	}
	else if (current_cst_node->node_type == INT_EXPR) {
		return_val = analyze_int_expr();
	}
	else if (current_cst_node->node_type == STRING_EXP) {
		return_val = analyze_string_expr();
	}
	else if (current_cst_node->node_type == BOOL_EXPR) {
		return_val = analyze_boolean_expr();
	}
	current_cst_node = current_cst_node->parent;
	return return_val;
}

//TODO add check that next xpr is int or valid id
//TODO fix return value
bool SemanticAnalyzer::analyze_int_expr()
{
	bool return_val = false;

	Tree::create_node(current_ast_node, DIGIT, current_cst_node->children[0]->token);

	if (current_cst_node->children.size() == 1) {
		return_val = true;
	}
	else {
		Tree::create_node(current_ast_node, ADD);
		current_cst_node = current_cst_node->children[2].get();
		return_val = analyze_expr();
		current_cst_node = current_cst_node->parent;
	}
	return true;
}

bool SemanticAnalyzer::analyze_string_expr()
{
	Tree::create_node(current_ast_node, STRING_EXP, current_cst_node->token);
	return true;
}

//TODO
bool SemanticAnalyzer::analyze_boolean_expr()
{
	bool return_val = false;

	//handles single bool values
	if (current_cst_node->children.size() == 1) {
		Tree::create_node(current_ast_node, BOOL, current_cst_node->children[0]->token);
		return_val = true;
	}
	else {


		TokenType check_against = B_TYPE;

		current_cst_node = current_cst_node->children[1].get();


		//if the expr is a variable find its type
		if (current_cst_node->children[0]->node_type == CHAR) {
			auto found_scope = Tree::find_var(current_scope_node, current_cst_node->children[0]->token->text[0]);

			if (found_scope == nullptr) {
				errors.push_back("ERROR Semantic Analysis - Boolean Expr - Variable (" + current_cst_node->children[0]->token->text + ") not declared");
				current_cst_node = current_cst_node->parent;
				return false;
			}

			if (!found_scope->initialized) {
				errors.push_back("ERROR Semantic Analysis - Boolean Expr - Variable (" + current_cst_node->children[0]->token->text + ") declared but not initialized");
				current_cst_node = current_cst_node->parent;
				return false;

			}
			found_scope->used = true;
			check_against = found_scope->type;
		}

		if (check_against == B_TYPE) {
			return_val = analyze_expr();
		}
		else {
			errors.push_back("error wrong type");
			current_cst_node = current_cst_node->parent;
			return false;
		}

		current_cst_node = current_cst_node->parent;

		Tree::create_node(current_ast_node, BOOL_OP, current_cst_node->children[2]->token);
		current_cst_node = current_cst_node->children[3].get();


		//if the expr is a variable find its type
		if (current_cst_node->children[0]->node_type == CHAR) {
			auto found_scope = Tree::find_var(current_scope_node, current_cst_node->children[0]->token->text[0]);

			if (found_scope == nullptr) {
				errors.push_back("ERROR Semantic Analysis - Boolean Expr - Variable (" + current_cst_node->children[0]->token->text + ") not declared");
				current_cst_node = current_cst_node->parent;
				return false;
			}
			if (!found_scope->initialized) {
				errors.push_back("ERROR Semantic Analysis - Boolean Expr - Variable (" + current_cst_node->children[0]->token->text + ") declared but not initialized");
				current_cst_node = current_cst_node->parent;
				return false;

			}

			found_scope->used = true;
			check_against = found_scope->type;
		}

		if (check_against == B_TYPE) {
			return_val = return_val & analyze_expr();
		}
		else {
			errors.push_back("error wrong type");
			current_cst_node = current_cst_node->parent;
			return false;
		}
		current_cst_node = current_cst_node->parent;

	}
	return return_val;
}

bool SemanticAnalyzer::type_check(const TokenType& var_type, const TokenType& expr_type)
{
	return (
		(var_type == I_TYPE && expr_type == INT_EXPR) ||
		(var_type == B_TYPE && expr_type == BOOL_EXPR) ||
		(var_type == S_TYPE && expr_type == STRING_EXP) ||
		(var_type == expr_type)
		);
}
