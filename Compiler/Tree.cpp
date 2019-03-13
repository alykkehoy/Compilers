#include "Tree.h"



Tree::Tree()
{
}


Tree::~Tree()
{
}

std::shared_ptr<tree_node> Tree::create_node(tree_node* parent, TokenType node_type)
{
	shared_ptr<tree_node> node(new tree_node);
	node->node_type = node_type;
	node->parent = parent;
	parent->children.push_back(node);

	return node;
}

void Tree::print_tree()
{
}
