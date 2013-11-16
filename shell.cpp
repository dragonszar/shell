//Shell Program
//Authors: Michael and Frank
//CS485-1
//Fall 2013

#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <unistd.h>

#include "command.cpp"
#include "parser.cpp"

using namespace std;


int main (int argc, char **argv)
{
  // Running the shell requires an unterminated loop to get new commands
  while( Command::quit == false )
  {
    cout << Command::prompt << " ";

    // Getting Input
    string cinput;
    getline(cin, cinput);

    Command::debug = true;

    Command c = parseForCommands(cinput);

    c.execute();
  }
  return 0;
}

