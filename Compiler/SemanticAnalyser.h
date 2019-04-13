#pragma once
#include <vector>
#include <iostream>
#include "Token.h"

struct table_row
{
	Token* token = nullptr;
};

struct table_node
{
	shared_ptr<table_node> parent;
	std::vector<std::shared_ptr<table_row>> rows;
	std::vector<std::shared_ptr<table_node>> children;
};

class SemanticAnalyser
{
public:
	SemanticAnalyser();
	~SemanticAnalyser();
};

