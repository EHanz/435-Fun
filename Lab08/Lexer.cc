/*
  Filename   : Lexer.cc
  Author     : 
  Course     : CSCI 435
  Assignment : Lab 5 - Lexing With Class
*/

/***********************************************************************/
// System includes

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

/***********************************************************************/
// Local includes

#include "Lexer.h"

/***********************************************************************/
// Using declarations

using std::cout;
using std::endl;
using std::string;
using std::stoi;

/***********************************************************************/

Lexer::Lexer (FILE* srcFile)
{
    m_srcFile = srcFile;
    m_columnNum = 1;
    m_lineNum = 1;
}

Lexer::~Lexer ()
{
    std::fclose (m_srcFile);
}

int
Lexer::getLineNum ()
{
    return m_lineNum;
}

int
Lexer::getColumnNum ()
{
    return m_columnNum;
}

int
Lexer::getChar ()
{
    fgetc (m_srcFile);
}

void
Lexer::ungetChar (int c)
{
    ungetc (c, m_srcFile);
}

Token
Lexer::lexId ()
{
    std::string id;
    std::string keywords[6] = {"if", "while", "int", "void", "return"};
    char c;
    while (isalpha (c))
    {
        id.push_back (c);
        c = getChar ();
    }

    if (!id.compare ("if"))
    {
        m_columnNum += id.length ();
        return Token (IF, "if");
    }
    else if (!id.compare ("while"))
    {
        m_columnNum += id.length ();
        return Token (WHILE, "while");
    }
    else if (!id.compare ("int"))
    {
        m_columnNum += id.length ();
        return Token (INT, "int");
    }
    else if (!id.compare ("void"))
    {
        m_columnNum += id.length ();
        return Token (VOID, "void");
    }
    else if (!id.compare ("return"))
    {
        m_columnNum += id.length ();
        return Token (RETURN, "return");
    }
    else
    {
        m_columnNum += id.length ();
        return Token (ID, id);
    }
    /*
    * do a loop and accumuluate all letters
    * see if its a keyword
    * store letters in a string
    * keep adding to the end since std::string is essentially a vector
    */
}

Token
Lexer::lexNum ()
{
    std::string strNum;
    char c;
    while (isdigit (c))
    {
        strNum.push_back (c);
        c = getChar ();
    }
    int intNum = stoi (strNum);
    return Token (NUM, strNum, intNum);
    //lexId but changes the string to an int
}

Token
Lexer::getToken () 
{   
  while (true)
  {
    char c = getChar ();

    if (isalpha (c))
      return lexId ();

    if (isdigit (c))
      return lexNum ();

    switch (c)
    {
      case '\n':
        ++m_lineNum;
        m_columnNum = 1;
        break;

      case EOF:
        return Token (END_OF_FILE);

    // Operators
      case '+':
        return Token (PLUS, "+");
      // c = getChar ();
      // if (c != '+')
      // {
      //   ungetChar (c);
      //   return Token (PLUS, "+");
      // }
      // return Token (INCREMENT, "++");  

      case '*':
        return Token (TIMES, "*");    

      case '<':
        c = getChar ();
        if (c != '=')
        {
          ungetChar (c);
          return Token (LT, "<");
        }
        return Token (LTE, "<=");

      case '>':
        c = getChar ();
        if (c != '=')
        {
          ungetChar (c);
          return Token (GT, ">");
        }
        return Token (GTE, ">=");

      case '=':
        c = getChar ();
        if (c != '=')
        {
          ungetChar (c);
          return Token (ASSIGN, "=");
        }
        return Token (EQ, "==");

      case '!':
        c = getChar ();
        if (c != '=')
        {
          ungetChar (c);
          m_columnNum++;
          return Token (ERROR, "!");
        }
        return Token (NEQ, "!=");

    // Punctuators
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
            
      case '/':
        c = getChar ();
        if(c != '/')
        {
            ungetChar (c);
            m_columnNum++;
            return Token (ERROR, "/");
        }
        return Token (COMMENT, "//");

      default:
        c = getChar ();
        std::string str(1, c);
        m_columnNum++;
        return Token (ERROR, str);
    }
  }
}

