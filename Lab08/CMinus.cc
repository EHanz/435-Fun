/*
    Filename    : CMinus.cc
    Author      : Lauren Deaver
    Course      : CSCI 435
    Assignment  : Lab 8 - CMinus Parser
*/


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "Lexer.h"
#include "Parser.h"

using std::cout;
using std::endl;

//extern FILE* yyin;
//extern char* yytext;
//extern int columnNum;
//extern int lineNum;

//extern "C"
//int
//yylex ();

int
main (int argc, char* argv[])
{
    ++argv;
    --argc;
    FILE* srcFile;
    if (argc > 0)
    {
        srcFile = fopen(argv[0], "r");
    }
    else 
    {
        srcFile = stdin;
    }
    Lexer lex(srcFile);

    
    std::vector<Token> tokenVector;
    tokenVector = lex.tokenize();
    
    Parser pars(tokenVector);
    pars.start();
    
    return EXIT_SUCCESS;
}