#include "Tree.h"



Tree::Tree()
{
}


Tree::~Tree()
{
}

tree_node* Tree::create_node(tree_node* parent, TokenType node_type)
{
	shared_ptr<tree_node> node(new tree_node);
	node->node_type = node_type;
	node->parent = parent;
	parent->children.push_back(node);

	return node.get();
}

void Tree::print_tree()
{
	expand(std::make_shared<tree_node> (head), 0);
}

void Tree::expand(std::shared_ptr<tree_node> node, int depth)
{
	for (int i = 0; i < depth; i++) {
		std::cout << "-";
	}

	// If there are no children (i.e., leaf nodes)...
	if (node->children.size() == 0) {
		// ... note the leaf node.
		std::cout << "[ " << print_token.print_token_type(node->node_type) << " ]" << std::endl;
	}
	else {
		// There are children, so note these interior/branch nodes and ...
		std::cout << "<" << print_token.print_token_type(node->node_type) << ">" << std::endl;
		// .. recursively expand them.
		for (int i = 0; i < node->children.size(); i++) {
			expand(node->children[i], depth + 1);
		}
	}
}
