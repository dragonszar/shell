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
  while( Command::quit == false )
  {
    cout << Command::prompt << " ";
    int child_pid;
    list<string> args;

    ///////////////////////////////////////////////////////////////////////////////////
    // Getting Input
    string cinput;
    cin >> cinput;

    list<Command> commands = parseForCommands(cinput);
    while (!commands.empty()) {
        commands.front().execute();
        commands.pop_front();
    }

    // Command example(cinput);
    // example.execute(); 

    // Command example2("dir",args,"","");
    // example2.execute();

    // args.push_back("..");
    // Command example3("chdir",args,"","");
    // example3.execute();
    // args.pop_front();

    // Command example4("dir",args,"","");
    // example4.execute();

    // Command example5("quit",args,"","");
    // example5.execute();


    ///////////////////////////////////////////////////////////////////////////////////
    //Send cinput to the Scanner and Parse here


    ///////////////////////////////////////////////////////////////////////////////////
    //Run Command
    /*
    if (true)//check if built in command
    {
      //run built in command
    }
    else
    {   
	    child_pid = fork();
        if (child_pid == 0)
		{
		  run_user_command(command);
		}
		else
		{
		  wait(child_pid);
		  exit(0);
		}
        
    }
    */
  }
}

