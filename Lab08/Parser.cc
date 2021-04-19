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
Parser::match (const std::string& function, TokenType expectedType)
{
    if (m_tokens[m_index].type == expectedType)
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
Parser::program()
{
    while (m_tokens[m_index].type != END_OF_FILE)
    {
        declarationList();
    }
}

//declarationList -> declaration {declaration}
void
Parser::declarationList()
{
    declaration();
    while((m_tokens[m_index].type == INT) | (m_tokens[m_index].type == VOID))
    {
        declaration();
    }

}

//declaration -> varDeclaration | funDeclaration
void
Parser::declaration()
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
Parser::varDeclaration()
{
    typeSpecifier();
    match("varDeclaration", ID);

    if (m_tokens[m_index].type == LBRACK)
    {
        match("varDeclaration", LBRACK);
        match("varDeclaration", NUM);
        match("varDeclaration", RBRACK);
    }
    else
    {
        match("varDeclaration", SEMI);
    }


}

//typeSpecifier -> 'INT' | 'VOID'
void 
Parser::typeSpecifier()
{
    if (m_tokens[m_index].type == INT)
    {
        match("typeSpecifier", INT);
    }
    else if (m_tokens[m_index].type == VOID)
    {
        match("typeSpecifier", VOID);
    }
    else
    {
        //error
    }

}

//funDeclaration -> typeSpecifier ID '(' params ')' compountStmt
void
Parser::funDeclaration()
{
    typeSpecifier();
    match("funDeclaration", ID);
    match("funDeclaration", LPAREN);
    params();
    match("funDeclaration", RPAREN);
    compoundStmt();

}

//params -> paramList | 'VOID'
void
Parser::params()
{
    if ((m_tokens[m_index].type == INT) | (m_tokens[m_index + 1].type == ID))
    {
        paramList();
    }
    else if ((m_tokens[m_index].type == VOID) && (m_tokens[m_index + 1].type == RPAREN))
    {
        match("params", VOID);
    }
    else
    {
        //error
    }
}

//paramList -> param { ',' param}
void
Parser::paramList()
{
    param();
    while(m_tokens[m_index].type == COMMA)
    {
        match("paramList", COMMA);
        param();
    }
}

//param -> typeSpecifier ID ['[' ']']
void
Parser::param()
{
    typeSpecifier();
    match("param", ID);
    if(m_tokens[m_index].type == LBRACK)
    {
        match("param", LBRACK);
        match("param", RBRACK);
    }

}

//compoundList -> '{' localDeclarations stmtList '}'
void
Parser::compoundStmt()
{
    match("compoundStmt", LBRACE);
    localDeclarations();
    stmtList();
    match("compountStmt", RBRACE);

}

//localDeclarations -> {varDeclaration}
void
Parser::localDeclarations()
{
    while((m_tokens[m_index].type == INT) | (m_tokens[m_index].type == VOID))
    {
        varDeclaration();
    }
}

// stmtList -> {stmt}
void
Parser::stmtList()
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
Parser::stmt()
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
Parser::expressionStmt()
{
    if ((m_tokens[m_index].type == ID) | (m_tokens[m_index].type == LPAREN) | (m_tokens[m_index].type == NUM))
    {
        expr();
    }
    match("expressionStmt", SEMI);

}

//selectionStmt -> 'IF' '(' expr ')' stmt [ 'ELSE' stmt ]
void
Parser::selectionStmt()
{
    match("selectionStmt", IF);
    match("selectionStmt", LPAREN);
    expr();
    match("selectionStmt", RPAREN);
    stmt();
    if(m_tokens[m_index].type == ELSE)
    {
        match("selectionStmt", ELSE);
        stmt();
    }

}

//iterationStmt -> 'WHILE' '(' expr ')' stmt
void
Parser::iterationStmt()
{
    match("iterationStmt", WHILE);
    match("iterationStmt", LPAREN);
    expr();
    match("iterationStmt", RPAREN);
    stmt();

}

//returnStmt -> 'RETURN' [expr] ';'
void
Parser::returnStmt()
{
    match("returnStmt", RETURN);
    if ((m_tokens[m_index].type == ID) | (m_tokens[m_index].type == LPAREN) | (m_tokens[m_index].type == NUM))
    {
        expr();
    }
    match("returnStmt", SEMI);

}

//expr -> var '=' expr | simpleExpr
void
Parser::expr()
{
    if (m_tokens[m_index + 1].type == ASSIGN)
    {
        var();
        match("expr", ASSIGN);
        expr();
    }
    else
    {
        simpleExpr();
    }

}

//var -> ID [ '[' expr ']' ]
void
Parser::var()
{
    match("var", ID);
    if (m_tokens[m_index].type == LBRACK)
    {
        match("var", LBRACK);
        expr();
        match("var", RBRACK);
    }

}

//simpleExpr -> additiveExpr {relop additiveExpr}
void
Parser::simpleExpr()
{
    additiveExpr();
    if ((m_tokens[m_index].type == LT) | (m_tokens[m_index].type == LTE) |
        (m_tokens[m_index].type == GT) | (m_tokens[m_index].type == GTE) |
        (m_tokens[m_index].type == EQ) | (m_tokens[m_index].type == NEQ))
    {
        relop();
        additiveExpr();
    }

}

//relop -> '<=' | '<' | '>' | '>=' | '==' |'!='
void
Parser::relop()
{
    if (m_tokens[m_index].type == LT)
    {
        match("additiveExpr", LT);
    }
    else if (m_tokens[m_index].type == LTE)
    {
        match("additiveExpr", LTE);
    }
    else if (m_tokens[m_index].type == GT)
    {
        match("additiveExpr", GT);
    }
    else if (m_tokens[m_index].type == GTE)
    {
        match("additiveExpr", GTE);
    }
    else if (m_tokens[m_index].type == EQ)
    {
        match("additiveExpr", EQ);
    }
    else if (m_tokens[m_index].type == NEQ)
    {
        match("additiveExpr", NEQ);
    }
    else
    {
        //error
    }
}

//additiveExpr -> term {addop term}
void
Parser::additiveExpr()
{
    term();
    if ((m_tokens[m_index].type == PLUS) | (m_tokens[m_index].type == MINUS))
    {
        addop();
        term();
    }

}

//addop -> '+' | '-'
void
Parser::addop()
{
    if (m_tokens[m_index].type == PLUS)
    {
        match("addop", PLUS);
    }
    else if (m_tokens[m_index].type == MINUS)
    {
        match("addop", MINUS);
    }
    else 
    {
        //error
    }

}

//term -> factor {mulop factor}
void
Parser::term()
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
Parser::mulop()
{
    if (m_tokens[m_index].type == TIMES)
    {
        match("mulop", TIMES);
    }
    else if (m_tokens[m_index].type == MINUS)
    {
        match("mulop", MINUS);
    }
    else
    {
        //error
    }
}

//factor -> '(' expr ')' | var | call | NUM
void
Parser::factor()
{
    if (m_tokens[m_index].type == LPAREN)
    {
        match("factor", LPAREN);
        expr();
        match("factor", RPAREN);
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
        match("factor", NUM);
    }
}

//call -> ID '(' args ')'
void
Parser::call()
{
    match("call", ID);
    match("call", LPAREN);
    args();
    match("call", RPAREN);
}

//args -> [argList]
void
Parser::args()
{
    if ((m_tokens[m_index].type == ID) | (m_tokens[m_index].type == LPAREN) | (m_tokens[m_index].type == NUM))
    {
        argList();
    }

}

//argList -> expr { ',' expr }
void
Parser::argList()
{
    expr();
    while (m_tokens[m_index].type == COMMA)
    {
        match("argList", COMMA);
        expr();
    }

}