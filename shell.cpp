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
<<<<<<< HEAD
=======

>>>>>>> b489ac6dafaed7d7f24e5cf746f8d3aa5165c07e
  // Running the shell requires an unterminated loop to get new commands
  while( Command::quit == false )
  {
    cout << Command::prompt << " ";

<<<<<<< HEAD
    // Getting Input
    string cinput;
    getline(cin, cinput);
    // cout << cinput << endl;

    Command::debug = true;

    Command c = parseForCommands(cinput);

    c.execute();
  }
  return 0;
}

