# Table of Contents

- [Compiling the Compiler](https://github.com/alykkehoy/Compilers#compiling-the-compiler)
- [Compiling a File](https://github.com/alykkehoy/Compilers#compiling-a-file)
  - [Lexing](https://github.com/alykkehoy/Compilers#lexing)
  - [Parsing](https://github.com/alykkehoy/Compilers#parsing)
  - [Semantic Analysis](https://github.com/alykkehoy/Compilers#semantic-analysis)

# Compiling the Compiler
#### Using g++
The compiler can be compiled using the following g++ comand:

`g++ -std=c++11 -o Compiler Compiler.cpp Lexer.cpp Token.cpp Program.cpp Parser.cpp Tree.cpp SemanticAnalizer.cpp`

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
## Lexing
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

#### Example
Here is an example output from the lex of `{int a}$`.
```
INFO Lexer - lexing program 1
DEBUG Lexer - L_Brace [ { ] found at (1:0)
DEBUG Lexer - Type [ int ] found at (1:1)
DEBUG Lexer - Char [ a ] found at (1:5)
DEBUG Lexer - R_Brace [ } ] found at (1:6)
INFO Lexer - Lex complete with 0 errors
```

## Parsing
#### Warnings
There are currently no warnings given by the parser.
#### Errors
If an error is found during parsing the following error message will be returned:
```
ERROR PARSER - TOKEN MISMATCH at (line number, position) expected: Token Type fount: Token Type
Parse failed
```
#### Completed
If no errors where found during parseing a message telling you the parse was successful will be displayed as well as the concrete syntax tree created during the parse.

#### Example
Here is an example output from the parse of `{int a}$`.
```
INFO Parser - parsing program 1
DEBUG Parser - parse block
DEBUG Parser - parse statement list
DEBUG Parser - parse statement
DEBUG Parser - parse var decl
DEBUG Parser - parse type
DEBUG Parser - parse id
DEBUG Parser - parse statement list
Parse complete

Program 1 CST:
< PROGRAM >
-< BLOCK >
--[ { ]
--< STATEMENT_LIST >
---< STATEMENT >
----< VARIABLE_DECLARATION >
-----[ int ]
-----[ a ]
---< STATEMENT_LIST >
--[ } ]

--------------------------------------
```

## Semantic Analysis 
#### Warnings
The Semantic Analyzer will display a warning if a variable has been declared but not used in any further pieces of code.
```
WARNING Semantic Analysis - Variable (variable name) declared but not used
```
#### Errors
If a piece of code attepmts to use a variable that has not been declared within its scope or a higher scope the following error will be displayed:
```
ERROR Semantic Analysis - Line: line number - Variable (variable name) not declared"
```

If a piece of code attepmts to use a variable that has been declared within its scope or a higher scope, but has not been initilized the following error will be displayed:
```
ERROR Semantic Analysis - Line: line number - Variable (variable name) declared but not initialized
```

If a piece of code attepmts to declare a variable with an id that has already been used the following error will be dispalyed:
```
ERROR Semantic Analysis - Line: line number - Variable Declaration - Variable (variable name) already declared"
```

If a piece of code attepmts to assign to a variable an expression of a different type than the variable's type the following error will be dispalyed:
```
ERROR Semantic Analysis - Line: line number - Variable (variable name) of type: type not: type

```
#### Completed
#### Example
Here is an example output from the Semantic Analyzer.

Source Code:
```
{
  int a
  a = 1
}$
```
Output:
```
Semantic Analysis:
Complete with 0 Errors
Complete with 1 Warnings:
WARNING Semantic Analysis - Variable (a) declared but not used

Program 1 AST:
< PROGRAM >
-< BLOCK >
--< VARIABLE_DECLARATION >
---< I_TYPE >
---[ a ]
--< ASSIGNMENT_STATEMENT >
---[ a ]
---[ 1 ]

Program 1 Symbol Table:
-----------------------
Name  Type  Scope  Line
-----------------------
 a   I_TYPE   0     1

--------------------------------------
```

