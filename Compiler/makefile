CC = g++
FLAGS = -std=c++11

TARGET = Compiler

default: Compiler

Compiler:
	$(CC) $(FLAGS) -o Compiler Compiler.cpp Token.cpp Lexer.cpp Program.cpp Parser.cpp Tree.cpp SemanticAnalyzer.cpp CodeGenerator.cpp

Compiler2: Compiler.o Token.o Lexer.o Program.o Parser.o Tree.o SemanticAnalyzer.o CodeGenerator.o
	$(CC) $(FLAGS) -o Compiler Compiler.o Token.o Lexer.o Program.o Parser.o Tree.o SemanticAnalyzer.o

Compiler.o: Compiler.cpp
	$(CC) $(FLAGS) -c Compiler.cpp

Token.o: Token.cpp Token.h
	$(CC) $(FLAGS) -c Token.cpp

Lexer.o: Lexer.cpp Lexer.h
	$(CC) $(FLAGS) -c Lexer.cpp

Program.o: Program.cpp Program.h
	$(CC) $(FLAGS) -c Program.cpp

Parser.o: Parser.cpp Parser.h
	$(CC) $(FLAGS) -c Parser.cpp

Tree.o: Tree.cpp Tree.h
	$(CC) $(FLAGS) -c Tree.cpp

SemanticAnalyzer.o: SemanticAnalyzer.cpp SemanticAnalyzer.h
	$(CC) $(FLAGS) -c SemanticAnalyzer.cpp

CodeGenerator.o: CodeGenerator.cpp CodeGenerator.h
	$(CC) $(FLAGS) -c CodeGenerator.cpp

clean:
	$(RM) *.o Compiler
