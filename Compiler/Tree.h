#pragma once
#include <iostream>
#include <vector>
#include "Token.h"

struct tree_node
{
	TokenType node_type;
	std::vector<std::shared_ptr<tree_node>> children;
};

class Tree
{
public:
	tree_node* head = new tree_node;

	Tree();
	~Tree();
	void print_tree();
};