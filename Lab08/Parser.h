#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <stdio>
#include "Lexer.h"

class Parser
{
    public :
        Parser (std::vector<Token> tokenVector);
        ~Parser ();

        void
        match ();

        void
        error ();

        void
        program();

        void
        declarationList();

        void
        declaration();

        void
        varDeclaration();

        void 
        typeSpecifier();

        void
        funDeclaration();

        void
        params();

        void
        paramList();

        void
        param();

        void
        compoundList();

        void
        localDeclarations();

        void
        stmtList();

        void
        stmt();

        void
        expressionStmt();

        void
        selectionStmt();

        void
        iterationStmt();

        void
        returnStmt();

        void
        expr();

        void
        var();

        void
        simpleExpr();

        void
        relop();

        void
        additiveExpr();

        void
        addop();

        void
        term();

        void
        mulop();

        void
        factor();

        void
        call();

        void
        args();

        void
        argList();

    private:
        std::vector<Token> m_tokens;
        int m_index;
};

#endif