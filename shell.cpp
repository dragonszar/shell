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
    int child_pid;
    list<string> args;

    // Getting Input
    string cinput;
    cin >> cinput;
    cout cinput;

    list<Command> commands = parseForCommands(cinput);
    Command::debug = true;

    while (!commands.empty()) {
        commands.front().execute();
        commands.pop_front();
    }
  }
}

