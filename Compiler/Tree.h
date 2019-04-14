#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Token.h"

struct scope_row
{
	Token* token = nullptr;
	TokenType type = NONE;
	bool initialized = false;
	bool used = false;
};

struct scope
{
	shared_ptr<scope> parent;
	std::vector<std::shared_ptr<scope_row>> rows;
	std::vector<std::shared_ptr<scope>> children;
};

struct tree_node
{
	TokenType node_type;
	Token* token = nullptr;
	tree_node* parent = nullptr;
	std::vector<std::shared_ptr<tree_node>> children;
};

class Tree
{
public:
	tree_node head;

	Tree();
	~Tree();
	static std::shared_ptr<scope_row> find_var(scope* current_scope, char var_id);
	static tree_node* create_node(tree_node* parent, TokenType node_type, Token* token = nullptr);
	static void print_scope_tree(const scope* scope_tree);
	void print_tree();

private:
	static void print_scope_table(const scope* scope_table);
	void expand(std::shared_ptr<tree_node> node, int depth);
};
