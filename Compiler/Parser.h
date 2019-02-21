#pragma once

#include <vector>
#include <iostream>

#include "Token.h"
#include "Program.h"

using namespace std;

class Parser
{
public:
	Parser();
	~Parser();

	void parse(Program& program);

private:

};

