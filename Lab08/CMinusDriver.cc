/*
    Filename: CMinus.cc
    Author: Evan Hanzelman
    Course: CSCI 435
    Assignment: Assignment 4
*/

#include <iostream>
#include <iomanip>
//#include <map>
#include <string>
#include <sstream>

#include "Lexer.h"

using std::cout;
using std::setw;

// extern "C"
// int
// yylex ();

//External variables needed for driver and lexer
//extern FILE* yyin;
//extern char* yytext;
//extern int cCount;
//extern int lCount;
//Creates a map of the tokens for the CMinus Language
std::string tokens [29] =
{
        "ERROR" ,
        "INT",
        "IF",
        "ELSE",
        "VOID",
        "RETURN",
        "WHILE",
        "PLUS",
        "MINUS",
        "TIMES",
        "DIVIDE",
        "LT",
        "LTE",
        "GT",
        "GTE",
        "EQ",
        "NEQ",
        "ASSIGN",
        "SEMI",
        "COMMA",
        "LPAREN",
        "RPAREN",
        "LBRACK",
        "RBRACK",
        "LBRACE",
        "RBRACE",
        "ID",
        "NUM"
};


//Main function for the CMinus driver 
int 
main (int argI, char* argC[])
{
    ++argI;
    --argC;

    FILE* srcFile;
    if (argI > 0)
    {
        srcFile = fopen (argC[0], "r");
    }
    else 
    {
        srcFile = stdin;
    }

    Lexer lex (srcFile);

    Token result;
    int token;
    std::string lexeme;
    int num;

    cout << std::left << setw (16) << "TOKEN" << setw (18) << "LEXEME" << "VALUE" << std::endl
                      << setw (16) << "=====" << setw (18) << "======" << "=====" << std::endl;
    
    do
    {
        result = lex.getToken ();
        token = result.type;
        lexeme = result.lexeme;
        num = result.number;
        
        std::cout << tokens [token] << "\t\t" << lexeme << "'\'\t\t";

        if (token == ID)
        {
            std::cout << "'\'" << lexeme << "'\'\n" ;
        }
        else if (token == NUM)
        {
            std::cout << '"' << num << '"';
        }
        else if (token == ERROR)
        {
            int cCount = lex.getColumnNum ();
            int lCount = lex.getLineNum ();
            std::cout << "Line: " << lCount << "; Column: " << cCount << "; ";
        }

        std::cout << std::endl;

    } while (token != 0);
    
    return EXIT_SUCCESS;
} 