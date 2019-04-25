#pragma once

#include "Program.h"
#include "Token.h"
#include "Tree.h"

class CodeGenerator
{
private:
    Program* current_program;
    Tree* current_ast;
    scope* current_scope_tree;

public:
    CodeGenerator(/* args */);
    ~CodeGenerator();

    void generate_code(Program& program);
};
