CC = g++
FLAGS = -std=c++11

TARGET = Compiler

default: Compiler

Compiler: Compiler.o Token.o Lexer.o Program.o Parser.o
	$(CC) $(FLAGS) -o Compiler Compiler.o Token.o Lexer.o Program.o Parser.o

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

clean:
	$(RM) *.o Compiler
