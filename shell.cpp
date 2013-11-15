//Shell Program
//Authors: Michael and Frank
//CS485-1
//Fall 2013

#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <unistd.h>

using namespace std;

#include "shell.h"

////////////////////////////////////////////////////////////////////////////////////////
//Global Variabe
string built_in_commands[6] = {"#", "setprompt", "debug", "chdir", "quit", "dir"};
string prompt =  "iosh% ";
bool quit = false;
bool debug = false;

int main (int argc, char **argv)
{

  cout << prompt << " ";

  //Runnin the shell requires an loop to always get new commands
  while( quit == false )
  {
    int child_pid;
    

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

    cout << prompt << " ";
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
  for (int i=0; i<6; i++)
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
  	string temp;
  	cin >> temp;
  	char * directory = new char[temp.size()+1];
  	strcpy (directory, temp.c_str());


  	int result = chdir(directory);
  	if (result != 0)
  	{
  		cout << "Problem with changing directory.\n";
  	}
  }

  if( cmd=="dir" )
  {	
    cout << "Directory Listing: " << get_current_dir_name() << "\n";
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
