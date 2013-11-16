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

  // Running the shell requires an loop to always get new commands

  // Running the shell requires an unterminated loop to get new commands

  while( Command::quit == false )
  {
    cout << Command::prompt << " ";
    list<string> args1,args;

    // Getting Input
    string cinput;
    cin >> cinput;

    args.push_back("on");

    args1.push_back("-a");
    args1.push_back("-l");


    Command example("debug", args, "", "");
    example.execute();
    Command example1("/bin/ls", args1, "","");///home/student/Downloads/shell/progoutput.txt");
    example1.execute();

    /*
    list<Command> commands = parseForCommands(cinput);

    list<Command> commands = parseForCommands(cinput);
    Command::debug = true;


    while (!commands.empty()) {
        commands.front().execute();
        commands.pop_front();
    }

    */


  }
}

