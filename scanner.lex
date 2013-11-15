%{
#include <string>
#include <list>

enum commandType { CTWord, CTString, CTMeta, CTComment, CTEOL };

class Token {
public:
    Token(std::string, commandType);

    commandType type;
    std::string text;
};

Token::Token(std::string txt, commandType tp) { type=tp; text=txt; }

std::list<Token> Tokens;

/**/

%}

DIGIT    [0-9]
META     [<>#]
NORMAL   [^<># \t\n\r\0'"]
ESCMETA  [\\\s\\<\\>\\#]

%%

{NORMAL}+[{NORMAL}|{ESCMETA}]*    {  // word
                //printf("A word: %s\n", yytext);
                std::string text = yytext;
                Token tkn (text, CTWord);
                Tokens.push_back(tkn);
                }

\"([^"\\]*(\\.[^"\\]*)*)\"        {  // string
                //printf("A string: %s\n", yytext);
                std::string text = yytext;
                Token tkn (text, CTString);
                Tokens.push_back(tkn);
                }

{META}          {  // meta-character
                //printf("A meta: %s\n", yytext);
                std::string text = yytext;
                Token tkn (text, CTMeta);
                Tokens.push_back(tkn);
                }

^#[.\t ]*$      {  // comment
                //printf("A comment: %s\n", yytext);
                std::string text = yytext;
                Token tkn (text, CTComment);
                Tokens.push_back(tkn);
                }

\n+             {  // end of line
                //printf("A new line\n");
                std::string text = yytext;
                Token tkn (text, CTEOL);
                Tokens.push_back(tkn);
                }

[\t ]+          /* eat up whitespace */

.               printf( "Unrecognized character: %s\n", yytext );

%%

std::list<Token> scan(std::string input)
{
    // char string[] = "/bin/cat < \"hello world\"";
    const char *cstr = input.c_str();
    YY_BUFFER_STATE yybuf = yy_scan_string(cstr);
    yylex();
    yy_delete_buffer(yybuf);
    return Tokens;
}