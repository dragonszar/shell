//Shell Program
//Authors: Michael and Frank
//CS485-1
//Fall 2013

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

#include "shell.h"
/*
//////////////////////////////////////////////////////////////////////////////////$
//Function Prototypes
bool is_built_in_command(string command);   //Determines if command is a built in $
void run_built_in_command(string command);  //Perfoms the Built-In command
void run_user_command(string command);      //Running user command
*/

////////////////////////////////////////////////////////////////////////////////////////
//Global Variabe
string built_in_commands[5] = {"#", "setprompt", "debug", "chdir", "quit"};
string prompt =  "iosh% ";
bool quit = false;
bool debug = false;

int main (int argc, char **argv)
{

  //Runnin the shell requires an loop to always get new commands
  while( quit == false )
  {
    int child_pid;
    cout << prompt;

    ///////////////////////////////////////////////////////////////////////////////////
    //Getting Input
    string cinput;
    cin >> cinput;


    ///////////////////////////////////////////////////////////////////////////////////
    //Send cinput to the Scanner and Parse here


    ///////////////////////////////////////////////////////////////////////////////////
    //Debug Mode Handlerd
    if (debug == true)
    {
      //do the debug
    }


    ///////////////////////////////////////////////////////////////////////////////////
    //Command Rumming
    if (is_built_in_command(cinput))
    {
      run_built_in_command(cinput);
    }
    else
    {   /*
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
        */
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////
//Function loops throught the global array built_in_commands to see if the given
//command is a built in command.
//Input:  a command
//Output: true if command is built in
//        false if command is not built in
bool is_built_in_command(string command)
{
  for (int i=0; i<5; i++)
    if (built_in_commands[i] == command)
      return true;

  return false;
}



//////////////////////////////////////////////////////////////////////////////////////
//Function handles  built in commands
//Input:  A build in command
//Output: None
void run_built_in_command(string command)
{
  string cmd = command;

  ///////////////////////////////////////////////////////////////////////////////////
  //comment  command
  if( cmd=="#" )
  {
    //nothing happens
  }

  if( cmd=="setprompt" )
  {
    cin >> prompt;
    prompt = prompt + " ";
  }

  if( cmd=="debug" )
  {
    //do something about the debug
  }

  if( cmd=="chdir" )
  {
    cout << "This is a change directory\n";
  }

  ///////////////////////////////////////////////////////////////////////////////////
  //quit command
  if( cmd=="quit" )
  {
    quit = true;
  }
}

void run_user_command(string command)
{

}
