#ifndef TOKEN_CPP
#define TOKEN_CPP

#include <string>
#include <list>

enum tkntype { TTWord, TTString, TTMeta, TTEOL };

std::string tkn_type_str[4] = { "Word", "String", "Meta", "EOL" };

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