# Table of Contents

- [Compiling the Compiler](https://github.com/alykkehoy/Compilers#compiling-the-compiler)
- [Compiling a File](https://github.com/alykkehoy/Compilers#compiling-a-file)
  - [Lexer](https://github.com/alykkehoy/Compilers#lexer)
  - [Parser](https://github.com/alykkehoy/Compilers#parser)

# Compiling the Compiler
#### Using g++
The compiler can be compiled using the following g++ comand:

`g++ -std=c++11 -o Compiler Compiler.cpp Lexer.cpp Token.cpp Program.cpp Parser.cpp`

#### Using the Makefile
Run `make` to compile using the makefile provided. A `make clean` option is also included.

# Compiling a File

There are 2 ways to compile a file.
First option is to run the compiler with no arguments to read the default `Text.txt`.
```
./compiler.exe
```
Second option is to provide a txt file as the first argument.
```
./compiler.exe filename.txt
```
If the compiler fails to read the the file, it will provide the following error message: `Could not open file: filename.txt`
## Lexer
#### Warnings
The first warning you might receive is `WARNING - EOP missing at EOF`. This will let you know the lexer did not find an ending `$` in the last program from your text file. The lexer will automatically add this `$` for you. After this point it will proceed with lexing the file.

Other warnings include `WARNING Lexer - no comment end found` and `WARNING Lexer - No end of string expression found`. These let you know the lexer did not find a `*/` closing a comment and did not find a `"` closing a string expression respectivaly. In both cases it will assume the rest of the file is included in the comment or string.

#### Errors
The main error you will run into is: `ERROR Lexer - Error (line number, position) unrecognized token: text`. This lets you know the lexer found a token it did not recognize in the grammer. It also lets you know the line number, position, and text it could not match.

A second error you might recieve is `ERROR Lexer - Invalid string expression "text"`. This lets you know that while the lexer found what it thought was a string expression the string itself violates the rules of the grammer.

At the end of lexing a list of all the errors will be printed out again. Example:
```
ERROR LIST:
ERROR Lexer - Error (1, 1) unrecognized token: @#!
ERROR Lexer - Invalid string expression "ASFJIO!"
```

#### Completed
Once the lexer is complete it will either say `INFO Lexer - Lex failed with number errors` or `INFO Lexer - Lex complete with 0 errors`.

## Parser
#### Warnings
There are currently no warnings given by the parser.
#### Errors
If an error is found during parsing the following error message will be returned:
```
ERROR PARSER - TOKEN MISMATCH at (line number, position) expected: Token Type fount: Token Type
Parse failed
```
#### Completed
If no errors where found during parseing the following message will be displayed:
```
Parse complete
```
