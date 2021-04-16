/*
  Filename   : Lexer.h
  Author     : 
  Course     : CSCI 435
  Assignment : Assignment 5 - Lexing With Class
*/

/***********************************************************************/

#ifndef LEXER_H
#define LEXER_H

/***********************************************************************/

#include <string>

/***********************************************************************/

enum TokenType
  {
   // Special tokens
   END_OF_FILE, ERROR, COMMENT,

   // Keywords
   IF, ELSE, INT, VOID, RETURN, WHILE,

   // Operators
   PLUS, MINUS, TIMES, DIVIDE, LT, LTE, GT, GTE, EQ, NEQ, ASSIGN,

   // Punctuators
   SEMI, COMMA, LPAREN, RPAREN, LBRACK, RBRACK, LBRACE, RBRACE,

   // Identifier and integer literals
   ID, NUM
  };

/***********************************************************************/

struct Token
{
  Token (TokenType pType = END_OF_FILE,
         std::string pLexeme = "",
         int pNumber = 0)
    : type (pType), lexeme (pLexeme), number (pNumber)
  {  }
  
  TokenType   type;
  std::string lexeme;
  int         number;
};

/***********************************************************************/

class Lexer
{
public:
  Lexer (FILE* srcFile);

  ~Lexer ();

  Token
  getToken ();

  int 
  getLineNum ();

  int 
  getColumnNum ();

  Token
  lexId ();

  Token
  lexNum ();

private:
  int
  getChar ();

  void
  ungetChar (int c);

private:
  FILE* m_srcFile;
  int   m_lineNum;
  int   m_columnNum;
};

/***********************************************************************/

#endif
