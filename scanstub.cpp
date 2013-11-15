#include <list>
#include <string>
#include <iostream>
#include "scanner.cpp"
#include "token.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    string types[8] = { "Word", "String", "Meta", "EOL" };

    // list<Token> tokens;
    list<Token> tokens = tokenize("#hello");
    list<Token>::iterator i;
    for (i = tokens.begin(); i != tokens.end(); ++i)
    {
        cout << i->text << " is a " << types[i->type] << endl;
    }
    return 0;
}