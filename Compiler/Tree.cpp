#include "Tree.h"



Tree::Tree()
{
}


Tree::~Tree()
{
}

std::shared_ptr<scope_row> Tree::find_var(scope* current_scope, char var_id)
{
	while (current_scope != nullptr) {
		for (int i = 0; i < current_scope->rows.size(); i++) {
			if (current_scope->rows[i]->token->text[0] == var_id) {
				return current_scope->rows[i];
			}
		}
		current_scope = current_scope->parent.get();
	}

	return nullptr;
}

tree_node* Tree::create_node(tree_node* parent, TokenType node_type, Token* token)
{
	shared_ptr<tree_node> node(new tree_node);
	node->node_type = node_type;
	node->parent = parent;
	node->token = token;
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
	if (node->token != nullptr && node->children.size() == 0) {
		// ... note the leaf node.
		std::cout << "[ " << node->token->text << " ]" << std::endl;

	}
	else {
		// There are children, so note these interior/branch nodes and ...
		std::cout << "< " << Token::print_token_type(node->node_type) << " >" << std::endl;
		// .. recursively expand them.
		for (int i = 0; i < node->children.size(); i++) {
			expand(node->children[i], depth + 1);
		}
	}
}
