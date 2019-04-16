CC = g++
FLAGS = -std=c++11

TARGET = Compiler

default: Compiler

Compiler:
	$(CC) $(FLAGS) -o Compiler Compiler.cpp Token.cpp Lexer.cpp Program.cpp Parser.cpp Tree.cpp SemanticAnalyzer.cpp

clean:
	$(RM) *.o Compiler
