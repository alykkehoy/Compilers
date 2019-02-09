#include <string>
#pragma once

using namespace std;

class Token
{
public:
	string regex_string;
	pair <int, int> position;

	Token();
	~Token();
};

