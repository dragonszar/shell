#ifndef SCANNER_CPP
#define SCANNER_CPP

#include <list>
#include <string>
#include "token.cpp"
#include "lex.yy.c"

using namespace std;
extern list<Token> lex_tokens;

list<Token> tokenize(string input)
{
    const char *cstr = input.c_str();
    YY_BUFFER_STATE yybuf = yy_scan_string(cstr);
    yylex();
    yy_delete_buffer(yybuf);

    // list<Token> lex_tokens;
    // lex_tokens.push_back(Token("/bin/ls", CTWord));
    return lex_tokens;
}

#endif