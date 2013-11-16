#ifndef PARSER_CPP
#define PARSER_CPP

#include <iostream>
#include <list>
#include <string>
#include "token.cpp"
#include "lex.yy.c"
#include "command.cpp"

using namespace std;
extern list<Token> lex_tokens;

list<Token> tokenize(string input)
{
    // clear tokens from last time (if any).
    lex_tokens.clear();

    // get non-const c-string version of input
    char cstr[input.size()+1];
    cstr[input.size()] = 0;
    memcpy(cstr,input.c_str(), input.size());

    // change flex input to cstr
    YY_BUFFER_STATE yybuf = yy_scan_string(cstr);
    
    yylex(); // run the flex scanner

    yy_delete_buffer(yybuf);
    
    return lex_tokens;
}

Command parseForCommands(string input)
{
    list<Token> tokens = tokenize(input);
    list<Token>::iterator it = tokens.begin();
    Command parsed_command;

    // print tokens if in debug mode.
    if (Command::debug) {
        while (it != tokens.end())
        {
            cout << tkn_type_str[it->type] << " token: " << it->text << endl;
            it++;
        }
        it = tokens.begin();
    }

    // First token should be a Word (name of program, etc.)
    if (it->type == TTWord) {
        parsed_command.name = it->text;
        ++it;

        // look at rest of tokens to see if they are arguments, etc.
        // stops at end of list or end of line.
        while (it != tokens.end() && it->type != TTEOL)
        {
            // Encountered word or string; probably a program argument.
            if (it->type == TTWord || it->type == TTString)
            {
                parsed_command.arguments.push_back(it->text);
            }

            // Encountered meta-char...
            else if (it->type == TTMeta) 
            {
                // infile delimiter. Look at following args to determine useage-correctness.
                if (it->text == "<")
                {
                    ++it;
                    if (it != tokens.end() && (it->type == TTWord || it->type == TTString))
                        parsed_command.infile = it->text;

                    else {
                        parsed_command.name = "PARSE_ERROR";
                        parsed_command.arguments.clear();
                        parsed_command.arguments.push_back("Expected infile.");
                        it = tokens.end();
                    }
                }


                // Outfile delimiter. Look at following args to determine useage-correctness.
                else if (it->text == ">")
                {
                    ++it;
                    if (it != tokens.end() && (it->type == TTWord || it->type == TTString))
                        parsed_command.outfile = it->text;

                    else {
                        parsed_command.name = "PARSE_ERROR";
                        parsed_command.arguments.clear();
                        parsed_command.arguments.push_back("Expected outfile.");
                        it = tokens.end();
                    }
                }


                // Comment delimiter. Ignore rest of tokens on this line.
                else if (it->text == "#")
                {
                    it = tokens.end();
                    continue;
                }

            } // end: meta-char branch


            // Unexpected token. Quit.
            else {
                parsed_command.name = "PARSE_ERROR";
                parsed_command.arguments.clear();
                parsed_command.arguments.push_back("Unexpected token.");
                it = tokens.end();
            }

            ++it; // move to next token.
        } // end: while arguments remain
    } // end: if first token is word

    // Error: expected first token to be a word or nothing.
    else if (it != tokens.end()) {
        parsed_command.name = "PARSE_ERROR";
        parsed_command.arguments.push_back("Expected first token to be a Word.");
    }

    return parsed_command;
}

#endif