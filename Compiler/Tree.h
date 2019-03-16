#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Token.h"

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
	static tree_node* create_node(tree_node* parent, TokenType node_type);
	static tree_node* create_node(tree_node* parent, TokenType node_type, Token* token);
	void print_tree();

private:
	void expand(std::shared_ptr<tree_node> node, int depth);
};
