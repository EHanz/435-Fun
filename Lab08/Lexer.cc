/*
    Filename    : Lexer.cc
    Author      : Lauren Deaver
    Course      : CSCI 435
    Assignment  : Lab 5 - Lexing with Class
*/

/***********************/
// System includes

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>

/***********************/
// Local includes

#include "Lexer.h"

/***********************/
// Using declarations

using std::cout;
using std::endl;
using std::string;
using std::stoi; 

/***********************/
Lexer::Lexer (FILE* srcFile)
{
    m_lineNum = 1;
    m_columnNum = 1;
    m_srcFile = srcFile;
    //fopen(m_srcFile, "r");
}

Lexer::~Lexer ()
{
    fclose(m_srcFile);
}

int
Lexer::getChar()
{
    ++m_columnNum;
    return fgetc(m_srcFile);
}

void
Lexer::ungetChar(int c)
{
    --m_columnNum;
    ungetc(c, m_srcFile);
}

int
Lexer::getLineNum()
{
    return m_lineNum;
}

int
Lexer::getColumnNum()
{
    return m_columnNum;
}

Token
Lexer::lexId()
{
    std::string id;
    char c = getChar();
    while (isalpha(c))
    {
        id.push_back(c);
        c = getChar();
    }
    ungetChar(c);
    if (!id.compare("if"))
    {
        return Token (IF, "if");
    }
    else if (!id.compare("else"))
    {
        return Token (ELSE, "else"); 
    }
    else if (!id.compare("int"))
    {
        return Token (INT, "int"); 
    }
    else if (!id.compare("void"))
    {
        return Token (VOID, "void"); 
    }
    else if (!id.compare("return"))
    {
        return Token (RETURN, "return"); 
    }
    else if (!id.compare("while"))
    {
        return Token (WHILE, "while"); 
    }
    else
    {
        return Token (ID, id);
    }
/* Say you want to lex an ID. 

lexId (…)
{
  String id; 
  While (…)
    Append to id
    Get a new char
}*/

    // do the loop and accumulate all the letters
    // see if its a keyword
    // can store letters in a string 
    //since std::string is vector in disguise can keep adding to the end
}

Token
Lexer::lexNum()
{
    std::string strNum;
    char c = getChar();
    while (isdigit(c))
    {
        strNum.push_back(c);
        c = getChar();
    }
    ungetChar(c);
    int intNum = stoi(strNum);
    return Token (NUM, strNum, intNum);
    //similar to lexId but change the string to int
}

Token
Lexer::getToken()
{
    while (true)
    {
        char c = getChar();
        if (isalpha (c))
        {
            ungetChar(c);
            return lexId();
        }
        if (isdigit (c))
        {
            ungetChar(c);
            return lexNum();
        }
        switch (c)
        {
            case '\n':
                ++m_lineNum;
                m_columnNum = 1;
                break;
            
            case ' ':
                break;
            
            case '\t':
                break;

            case EOF:
                return Token (END_OF_FILE);

            //Operators
            case '+':
                return Token (PLUS, "+");
            /*if (c != '+')
            {
                ungetChar(c);
                return Token (PLUS, "+");
            }
            return Token (INCREMENT, "++");*/
            case '-':
                return Token (MINUS, "-");

            case '*':
                return Token (TIMES, "*");

            case '/':
                c = getChar();
                if (c == '*')
                {
                    while(true)
                    {
                        c = getChar();
                        if (c == '*')
                        {
                            c = getChar();
                            if (c == '/')
                            {
                                break;
                            }
                        }
                    }
                }
                else
                {
                    ungetChar(c);
                    return Token (DIVIDE, "/");
                }

            case '<':
                c = getChar();
                if (c != '=')
                {
                    ungetChar(c);
                    return Token (LT, "<");
                }
                return Token (LTE, "<=");

            case '>':
                c = getChar();
                if (c != '=')
                {
                    ungetChar(c);
                    return Token (GT, ">");
                }
                return Token (GTE, ">=");

            case '=':
                c = getChar();
                if (c != '=')
                {
                    ungetChar(c);
                    return Token (ASSIGN, "=");
                }
                return Token (EQ, "==");
            
            case '!':
                c = getChar();
                if (c != '=')
                {
                    ungetChar(c);
                    return Token (ERROR, "!");
                }
                return Token (NEQ, "!=");

            //Puncuators
            case ';':
                return Token (SEMI, ";");
            
            case ',':
                return Token (COMMA, ",");

            case '(':
                return Token (LPAREN, "(");

            case ')':
                return Token (RPAREN, ")");

            case '[':
                return Token (LBRACK, "[");
            
            case ']':
                return Token (RBRACK, "]");

            case '{':
                return Token (LBRACE, "{");

            case '}':
                return Token (RBRACE, "}");

            default:
                std::string err;
                err.push_back(c);
                return Token (ERROR, err);
        }
    }
}

