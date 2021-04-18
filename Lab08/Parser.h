#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <stdio>
#include "Lexer.h"

class Parser
{
    public :
        Parser ();
        ~Parser ();

        void
        match ();

        void
        error ();
};

#endif