#ifndef TOKEN_CPP
#define TOKEN_CPP

#include <string>
#include <list>

enum tkntype { 
    CTWord,     CTString, 
    CTMeta,     CTEOL 
};

class Token {
public:
    Token(std::string, tkntype);

    tkntype type;
    std::string text;
};

Token::Token(std::string txt, tkntype tp)
{
    text=txt; 
    type=tp; 
}

#endif