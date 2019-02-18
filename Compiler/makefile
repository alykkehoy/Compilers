CC = g++
FLAGS = -std=c++11

TARGET = Compiler

default: Compiler

Compiler: Compiler.o Token.o Lexer.o
	$(CC) $(FLAGS) -o Compiler Compiler.o Token.o Lexer.o

Compiler.o: Compiler.cpp
	$(CC) $(FLAGS) -c Compiler.cpp

Token.o: Token.cpp Token.h
	$(CC) $(FLAGS) -c Token.cpp

Lexer.o: Lexer.cpp Lexer.h
	$(CC) $(FLAGS) -c Lexer.cpp

clean:
	$(RM) *.o Compiler
