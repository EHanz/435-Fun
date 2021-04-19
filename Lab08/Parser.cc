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
Parser::match (const string& function, string expectedType)
{
    if (m_tokens[m_index].lexeme == expectedType)
    {
        m_index++;
    }
    else
    {
        //error
    }

}

void
Parser::error ()
{

}

//program -> declarationList
void
program()
{
    while (m_tokens[m_index].type != END_OF_FILE)
    {
        declarationList();
    }
}

//declarationList -> declaration {declaration}
void
declarationList()
{
    declaration();
    while((m_tokens[m_index].type == INT) | (m_tokens[m_index].type == VOID))
    {
        declaration();
    }

}

//declaration -> varDeclaration | funDeclaration
void
declaration()
{
    if (m_tokens[m_index + 2].type == LPAREN)
    {
        funDeclaration();
    }
    else if (m_tokens[m_index + 2].type == LBRACK)
    {
        varDeclaration();
    }
    else
    {
        //error
    }

}

//varDeclaration -> typeSpecifier 'ID' [ '[' 'NUM' ']' ] ';'
void
varDeclaration()
{
    typeSpecifier();
    match("varDeclaration", <TokenType>ID);

    if (m_tokens[m_index].type == LBRACK)
    {
        match("varDeclaration", <TokenType>LBRACK);
        match("varDeclaration", <TokenType>NUM);
        match("varDeclaration", <TokenType>RBRACK);
    }
    else
    {
        match("varDeclaration", <TokenType>SEMI);
    }


}

//typeSpecifier -> 'INT' | 'VOID'
void 
typeSpecifier()
{
    if (m_tokens[m_index].type == INT)
    {
        match("typeSpecifier", <TokenType>INT)
    }
    else if (m_tokens[m_index].type == VOID)
    {
        match("typeSpecifier", <TokenType>VOID);
    }
    else
    {
        //error
    }

}

//funDeclaration -> typeSpecifier ID '(' params ')' compountStmt
void
funDeclaration()
{
    typeSpecifier();
    match("funDeclaration", <TokenType>ID);
    match("funDeclaration", <TokenType>LPAREN);
    params();
    match("funDeclaration", <TokenType>RPAREN);
    compoundStmt();

}

//params -> paramList | 'VOID'
void
params()
{
    if ((m_tokens[m_index].type == INT) | (m_tokens[m_index + 1].type) == ID)
    {
        paramList();
    }
    else if ((m_tokens[m_index].type == VOID) && (m_tokens[m_index + 1].type == RPAREN))
    {
        match("params", <TokenType>VOID);
    }
    else
    {
        //error
    }
}

//paramList -> param { ',' param}
void
paramList()
{
    param();
    while(m_tokens[m_index].type == COMMA)
    {
        match("paramList", <TokenType>COMMA);
        param();
    }
}

//param -> typeSpecifier ID ['[' ']']
void
param()
{
    typeSpecifier();
    match("param", <TokenType>'ID');
    if(m_tokens[m_index].type == LBRACK)
    {
        match("param", <TokenType>LBRACK);
        match("param", <TokenType>RBRACK);
    }

}

//compoundList -> '{' localDeclarations stmtList '}'
void
compoundStmt()
{
    match("compoundStmt", <TokenType>LBRACE);
    localDeclarations();
    stmtList();
    match("compountStmt", <TokenType>RBRACE);

}

//localDeclarations -> {varDeclaration}
void
localDeclarations()
{
    while((m_tokens[m_index].type == INT) | (m_tokens[m_index].type == VOID)
    {
        varDeclaration();
    }
}

// stmtList -> {stmt}
void
stmtList()
{
    while((m_tokens[m_index].type == ID) | (m_tokens[m_index].type == SEMI) |
            (m_tokens[m_index].type == LBRACE) | (m_tokens[m_index].type == IF) |
            (m_tokens[m_index].type == WHILE) | (m_tokens[m_index].type == RETURN))
    {
        stmt();
    }
}

//stmt -> expressionStmt | compoundStmt | selectionStmt | iterationStmt | returnStmt
void
stmt()
{
    if ((m_tokens[m_index].type == ID) | (m_tokens[m_index].type == SEMI))
    {
        expressionStmt();
    }
    else if (m_tokens[m_index].type == LBRACE)
    {
        compoundStmt();
    }
    else if (m_tokens[m_index].type == IF)
    {
        selectionStmt();
    }
    else if (m_tokens[m_index].type == WHILE)
    {
        iterationStmt();
    }
    else if (m_tokens[m_index].type == RETURN)
    {
        returnStmt();
    }
    else
    {
        //error
    }

}

// expresionStmt -> [expr] ';'
void
expressionStmt()
{
    if ((m_tokens[m_index].type == ID) | (m_tokens[m_index].type == LPAREN) | (m_tokens[m_index].type == NUM)
    {
        expr();
    }
    match("expressionStmt", <TokenType>SEMI)

}

//selectionStmt -> 'IF' '(' expr ')' stmt [ 'ELSE' stmt ]
void
selectionStmt()
{
    match("selectionStmt", <TokenType>IF);
    match("selectionStmt", <TokenType>LPAREN);
    expr();
    match("selectionStmt", <TokenType>RPAREN);
    stmt();
    if(m_tokens[m_index].type == ELSE)
    {
        match("selectionStmt", <TokenType>ELSE;
        stmt();
    }

}

//iterationStmt -> 'WHILE' '(' expr ')' stmt
void
iterationStmt()
{
    match("iterationStmt", <TokenType>WHILE);
    match("iterationStmt", <TokenType>LPAREN);
    expr();
    match("iterationStmt", <TokenType>RPAREN);
    stmt();

}

//returnStmt -> 'RETURN' [expr] ';'
void
returnStmt()
{
    match("returnStmt", <TokenType>RETURN);
    if ((m_tokens[m_index].type == ID) | (m_tokens[m_index].type == LPAREN) | (m_tokens[m_index].type == NUM))
    {
        expr();
    }
    match("returnStmt", <TokenType>SEMI);

}

//expr -> var '=' expr | simpleExpr
void
expr()
{
    if (m_tokens[m_index + 1].type == ASSIGN)
    {
        var();
        match("expr", <TokenType>ASSIGN);
        expr();
    }
    else
    {
        simpleExpr();
    }

}

//var -> ID [ '[' expr ']' ]
void
var()
{
    match("var", <TokenType>ID);
    if (m_tokens[m_index].type == LBRACK)
    {
        match("var", <TokenType>LBRACK);
        expr();
        match("var", <TokenType>RBRACK);
    }

}

//simpleExpr -> additiveExpr {relop additiveExpr}
void
simpleExpr()
{
    additiveExpr();
    if ((m_tokens[m_index].type == LT) | (m_tokens[m_index].type == LTE) |
        (m_tokens[m_index].type == GT) | (m_tokens[m_index].type == GTE) |
        (m_tokens[m_index].type == EQ) | (m_tokens[m_index].type == NEQ)
    {
        relop();
        additiveExpr();
    }

}

//relop -> '<=' | '<' | '>' | '>=' | '==' |'!='
void
relop()
{
    if (m_tokens[m_index].type == LT)
    {
        match("additiveExpr", <TokenType>LT);
    }
    else if (m_tokens[m_index].type == LTE)
    {
        match("additiveExpr", <TokenType>LTE);
    }
    else if (m_tokens[m_index].type == GT)
    {
        match("additiveExpr", <TokenType>GT);
    }
    else if (m_tokens[m_index].type == GTE)
    {
        match("additiveExpr", <TokenType>GTE);
    }
    else if (m_tokens[m_index].type == EQ)
    {
        match("additiveExpr", <TokenType>EQ);
    }
    else if (m_tokens[m_index].type == NEQ)
    {
        match("additiveExpr", <TokenType>NEQ);
    }
    else
    {
        //error
    }
}

//additiveExpr -> term {addop term}
void
additiveExpr()
{
    term()
    if ((m_tokens[m_index].type == PLUS) | (m_tokens[m_index].type == MINUS))
    {
        addop();
        term();
    }

}

//addop -> '+' | '-'
void
addop()
{
    if (m_tokens[m_index].type == PLUS)
    {
        match("addop", <TokenType>PLUS);
    }
    else if (m_tokens[m_index].type == MINUS)
    {
        match("addop", <TokenType>MINUS);
    }
    else 
    {
        //error
    }

}

//term -> factor {mulop factor}
void
term()
{
    factor();
    if ((m_tokens[m_index].type == TIMES) | (m_tokens[m_index].type == DIVIDE))
    {
        mulop();
        factor();
    }

}

//mulop -> '*' | '/'
void
mulop()
{
    if (m_tokens[m_index].type == TIMES)
    {
        match("mulop", <TokenType>TIMES);
    }
    else if (m_tokens[m_index].type == MINUS)
    {
        match("mulop", <TokenType>MINUS);
    }
    else
    {
        //error
    }
}

//factor -> '(' expr ')' | var | call | NUM
void
factor()
{
    if (m_tokens[m_index].type == LPAREN)
    {
        match("factor", <TokenType>LPAREN);
        expr();
        match("factor", <TokenType>RPAREN);
    }
    else if ((m_tokens[m_index].type == ID) && (m_tokens[m_index + 1].type == LPAREN))
    {
        call();
    }
    else if (m_tokens[m_index].type == ID)
    {
        var();
    }
    else if (m_tokens[m_index].type == NUM)
    {
        match("factor", <TokenType>NUM);
    }
}

//call -> ID '(' args ')'
void
call()
{
    match("call", <TokenType>ID);
    match("call", <TokenType>LPAREN);
    args();
    match("call", <TokenType>RPAREN);
}

//args -> [argList]
void
args()
{
    if ((m_tokens[m_index].type == ID) | (m_tokens[m_index].type == LPAREN) | (m_tokens[m_index].type == NUM)
    {
        argList();
    }

}

//argList -> expr { ',' expr }
void
argList()
{
    expr();
    while (m_tokens[m_index].type == COMMA)
    {
        match("argList", <TokenType>COMMA);
        expr();
    }

}