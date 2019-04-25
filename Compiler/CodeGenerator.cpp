#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(/* args */)
{
}

CodeGenerator::~CodeGenerator()
{
}

void CodeGenerator::generate_code(Program& program)
{
    this->current_program = &program;
    this->current_ast = &program.ast;
    this->current_scope_tree = &program.scope_tree;
}