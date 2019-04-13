#pragma once
#include "Program.h"

class SemanticAnalyzer
{
public:
	SemanticAnalyzer();
	~SemanticAnalyzer();

	void analyze(Program& program);
};

