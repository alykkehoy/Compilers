#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Token.h"

struct tree_node
{
	TokenType node_type;
	//std::shared_ptr<tree_node> parent = nullptr;
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
	tree_node* create_node(tree_node* parent, TokenType node_type);
	tree_node* create_node(tree_node* parent, TokenType node_type, Token* token);
	void print_tree();

private:
	Token print_token;

	void expand(std::shared_ptr<tree_node> node, int depth);
};
