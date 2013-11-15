#ifndef PARSER_CPP
#define PARSER_CPP

#include <list>
#include <string>
#include "token.cpp"
#include "lex.yy.c"
#include "command.cpp"

using namespace std;
extern list<Token> lex_tokens;

list<Token> tokenize(string input)
{
    const char *cstr = input.c_str();
    YY_BUFFER_STATE yybuf = yy_scan_string(cstr);
    yylex();
    yy_delete_buffer(yybuf);
    return lex_tokens;
}

list<Command> parseForCommands(string input)
{
    list<Token> tokens = tokenize(input);
    list<Command> parsed_commands;
    list<Token>::iterator it = tokens.begin();

    // First token should be a Word (name of program, etc.)
    if (it->type == CTWord) {
        Command cmd (it->text);
        ++it;

        // look at rest of tokens to see if they are arguments, etc.
        // stops at end of list or end of line.
        while (it != tokens.end() && it->type != CTEOL)
        {
            // Encountered word or string; probably a program argument.
            if (it->type == CTWord || it->type == CTString)
            {
                cmd.arguments.push_back(it->text);
            }

            // Encountered meta-char...
            else if (it->type == CTMeta) 
            {
                // infile delimiter. Look at following args to determine useage-correctness.
                if (it->text == "<")
                {
                    ++it;
                    if (it != tokens.end() && (it->type == CTWord || it->type == CTString))
                        cmd.infile = it->text;

                    else {
                        parsed_commands.clear();
                        cmd = Command("PARSE_ERROR");
                        cmd.arguments.push_back("Expected infile.");
                        parsed_commands.push_back(cmd);
                        return parsed_commands;
                    }
                }

                // Outfile delimiter. Look at following args to determine useage-correctness.
                else if (it->text == ">")
                {
                    ++it;
                    if (it != tokens.end() && (it->type == CTWord || it->type == CTString))
                        cmd.outfile = it->text;

                    else {
                        parsed_commands.clear();
                        cmd = Command("PARSE_ERROR");
                        cmd.arguments.push_back("Expected outfile.");
                        parsed_commands.push_back(cmd);
                        return parsed_commands;
                    }
                }

                // Comment delimiter. Ignore rest of tokens on this line.
                else if (it->text == "#")
                {
                    while (it != tokens.end() && it->type != CTEOL) 
                        ++it;
                    continue;
                }

            } // end: meta-char branch
            
            // Unexpected token. Quit.
            else {
                parsed_commands.clear();
                cmd = Command("PARSE_ERROR");
                cmd.arguments.push_back("Unexpected token.");
                parsed_commands.push_back(cmd);
                return parsed_commands;
            }

            ++it; // move to next token.
        } // end: while arguments remain

        parsed_commands.push_back(cmd);
    } // end: if first token is word

    // Error: expected first token to be a word.
    else {
        Command cmd ("PARSE_ERROR");
        cmd.arguments.push_back("Expected first token to be a Word.");
        parsed_commands.push_back(cmd);
        return parsed_commands;
    }

    if (it != tokens.end()) ++it;

    // while (it != tokens.end()) {   } // end: while commands remain
        
    
    return parsed_commands;
}

#endif