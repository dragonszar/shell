//Shell Program
//Authors: Michael and Frank
//CS485-1
//Fall 2013

#include <iostream>
#include <cstring>
#include <string>
#include "shell.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////////////
//Global Variabe
char *built_in_commands[5] = {"#", "setprompt", "debug", "chdir", "quit"};
bool quit = false;
bool debug = false;

int main (int argc, char **argv)
{

  //Runnin the shell requires an loop to always get new commands
  while( quit == false )
  {
    int child_pid;

    ///////////////////////////////////////////////////////////////////////////////////
    //Getting Input
    string input = "";                   // Used to get input from the user
    char * cinput = NULL;                // Used to store C-style version of the input
    getline (cin, input);	         // Getting input from user
    cinput = new char [input.size()+1];
    strcpy (cinput, input.c_str());    	 // Getting C-style version of user's input

    ///////////////////////////////////////////////////////////////////////////////////
    //Send cinput to the Scanner and Parse here


    ///////////////////////////////////////////////////////////////////////////////////
    //Debug Mode Handler
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
bool is_built_in_command(char * command)
{
  int i=0;
  while(built_in_commands[i])
  {
    if( strcmp(built_in_commands[i],command) == 0 )
    {
      return true;
    }
    i++;
  }
  return false;
}



//////////////////////////////////////////////////////////////////////////////////////
//Function handles  built in commands
//Input:  A build in command
//Output: None
void run_built_in_command(char * command)
{
  char * cmd = command;

  ///////////////////////////////////////////////////////////////////////////////////
  //comment  command
  if( strcmp(cmd,"#") == 0 )
  {
    //nothing happens
  }

  if( strcmp(cmd,"setprompt") == 0 )
  {
    cout << "This is setprompt\n";
  }

  if( strcmp(cmd,"debug") == 0 )
  {
    //do something about the debug
  }

  if( strcmp(cmd,"chdir") == 0 )
  {
    cout << "This is a change directory\n";
  }

  ///////////////////////////////////////////////////////////////////////////////////
  //quit command
  if( strcmp(cmd,"quit") == 0 )
  {
    quit = true;
  }
}

void run_user_command(char * command)
{

}
