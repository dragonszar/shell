%{
    #include "shell.h"

    token tokens[80];
    int tokenc = 0;
%}

DIGIT    [0-9]
META     [<>#]
NORMAL   [^<># \t\n\r\0'"]
ESCMETA  [\\\s\\<\\>\\#]

%%

{NORMAL}+[{NORMAL}|{ESCMETA}]*    {
                printf("A word: %s\n", yytext);
                Token token;
                token.string = yytext;
                token.type = 1;
                tokens[tokenc++] = token;
                }

\"([^"\\]*(\\.[^"\\]*)*)\"        {
                printf("A string: %s\n", yytext);
                Token token;
                token.string = yytext;
                token.type = 2;
                tokens[tokenc++] = token;
                }

{META}          {
                printf("A meta: %s\n", yytext);
                Token token;
                token.string = yytext;
                token.type = 3;
                tokens[tokenc++] = token;
                }

^#[.\t ]*$      {
                printf("A comment: %s\n", yytext);
                Token token;
                token.string = yytext;
                token.type = 4;
                tokens[tokenc++] = token;
                }

\n+             {
                printf("A new line\n");
                Token token;
                token.string = yytext;
                token.type = 0;
                tokens[tokenc++] = token;
                }

[\t ]+          /* eat up whitespace */

.               printf( "Unrecognized character: %s\n", yytext );

%%

int main( int argc, char **argv )
{
    char string[] = "/bin/cat < \"hello world\"";
    YY_BUFFER_STATE yybuf = yy_scan_string(string);
    yylex();
    yy_delete_buffer(yybuf);
}