#pragma once
#include <iostream>
#include <vector>
#include "Token.h"

struct tree_node
{
	TokenType node_type;
	//std::shared_ptr<tree_node> parent = nullptr;
	tree_node* parent = nullptr;
	std::vector<std::shared_ptr<tree_node>> children;
};

class Tree
{
public:
	tree_node head;

	Tree();
	~Tree();
	std::shared_ptr<tree_node> create_node(tree_node* parent, TokenType node_type);
	void print_tree();
};