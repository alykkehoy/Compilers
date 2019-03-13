#include "Program.h"

Program::Program()
{

}

Program::Program(int program_num, string program_text)
{
	this->program_num = program_num;
	this->program_text = program_text;
	cst.head.node_type = PROGRAM;
}


Program::~Program()
{
}
