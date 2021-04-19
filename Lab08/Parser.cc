#include "Parser.h"

Parser::Parser(std::vector<Token> tokenVector)
{
    m_tokens = tokenVector;
    m_index = 0;
}

Parser::~Parser()
{

}

void
Parser::match ()
{

}

void
Parser::error ()
{

}

//program -> declarationList
void
program()
{

}

//declarationList -> declaration {declaration}
void
declarationList()
{

}

//declaration -> varDeclaration | funDeclaration
void
declaration()
{

}

//carDeclaration -> typeSpecifier ID [ '[' NUM ']' ] ';'
void
varDeclaration()
{

}

//typeSpecifier -> 'INT' | 'VOID'
void 
typeSpecifier()
{

}

//funDeclaration -> typeSpecifier ID '(' params ')' compountStmt
void
funDeclaration()
{

}

//params -> paramList | 'VOID'
void
params()
{

}

//paramList -> param { ',' param}
void
paramList()
{

}

//param -> typeSpecifier ID ['[' ']']
void
param()
{

}

//compoundList -> '{' localDeclarations stmtList '}'
void
compoundList()
{

}

//localDeclarations -> {varDeclarations}
void
localDeclarations()
{

}

// stmtList -> {stmt}
void
stmtList()
{

}

//stmt -> expressionStmt | compoundStmt | selectionStmt | iterationStmt | returnStmt
void
stmt()
{

}

// expresionStmt -> [expr] ';'
void
expressionStmt()
{

}

//selectionStmt -> 'IF' '(' expr ')' stmt [ 'ELSE' stmt ]
void
selectionStmt()
{

}

//iterationStmt -> 'WHILE' '(' expr ')' stmt
void
iterationStmt()
{

}

//returnStmt -> 'RETURN' [expr] ';'
void
returnStmt()
{

}

//expr -> var '=' expr | simpleExpr
void
expr()
{

}

//var -> ID [ '[' expr ']' ]
void
var()
{

}

//simpleExpr -> additiveExpr {relop additiveExpr}
void
simpleExpr()
{

}

//relop -> '<=' | '<' | '>' | '>=' | '==' |'!='
void
relop()
{

}

//additiveExpr -> term {addop term}
void
additiveExpr()
{

}

//addop -> '+' | '-'
void
addop()
{

}

//term -> factor {mulop factor}
void
term()
{

}

//mulop -> '*' | '/'
void
mulop()
{

}

//factor -> '(' expr ')' | var | call | NUM
void
factor()
{

}

//call -> ID '(' args ')'
void
call()
{

}

//args -> [argList]
void
args()
{

}

//argList -> expr { ',' expr }
void
argList()
{

}