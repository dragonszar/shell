//Shell Program
//Authors: Michael and Frank
//CS485-1
//Fall 2013

#ifndef COMMAND_CPP
#define COMMAND_CPP

#include <string>       //For String
#include <iostream>     //For standard output
#include <fstream>      //For file redirections
#include <sys/stat.h>   ///
#include <cerrno>       ///
#include <fcntl.h>      /// For Forkings, PID, Wait......
#include <sys/types.h>  ///
#include <sys/wait.h>   ///
#include <cstring>      //For Chracter string
#include <list>         //For List Support
#include <unistd.h>     //For Directory
#include <stdio.h>      ///
#include <stdlib.h>     /// 

using namespace std;

class Command
{
public:
    //Constructor/Destructor
    Command ();
    Command (string);
    Command (string n, list<string> arg, string in, string out);
    ~Command ();
    
    
    //For Running Commands
    void execute();
    //Converting argument list to an array of character arrays
    void prepare_argv();
    //Running User Commands
    void run_cmd();
    //For Running Built in Commands
    bool run_built_in_command(string command);

    //string to_string();

    static string prompt;   //Used for storing current prompt
    static bool debug;      //Used for activating debug
    static bool quit;       //Used for contolling while loop in main

    list<string> arguments; //argument for this comand

    string name;            //command name
    string infile;          //full directory of infile
    string outfile;         //full directory of outfile

    char** argv;            //arguments 1.command ... arguments.... last-NULL
    int argc;               //number of arguments in argv
};


//Setting initial conditions for the shell
string Command::prompt =  "iosh% ";
bool Command::debug = false;
bool Command::quit = false;

// Constructor
Command::Command() {}
Command::Command (string n) { name = n; }
Command::~Command () {}
Command::Command (string n, list<string> arg, string in, string out) 
{ 
	name = n; 
	arguments = arg;
	infile = in;
	outfile = out;
}


//////////////////////////////////////////////////////////////////////////////////////
//Function handles execution of the command. It first runs the command name through
//run_built_in_command to see if the command. If the current command is not built in
//it will run run_cmd as a user command;
//Input:  None
//Output: None
void Command::execute() 
{ 
  if( run_built_in_command(name) != true)
  {
  	run_cmd();
  }   
}


//////////////////////////////////////////////////////////////////////////////////////
//Function takes the argument list, and converts it into an array of character arrays
//argv and store the number of members in argc
//Input:  None
//Output: None
void Command::prepare_argv()
{
	int size = arguments.size();
	char* temp = new char[name.size()+1];
	strcpy(temp, name.c_str());

	argc = size+2;
	argv = new char*[argc];
	argv[0] = temp;

  list<string>::iterator it = arguments.begin();

	for (int i=0; i<size; i++)
	{
		temp = new char[it->size()+1];
		strcpy (temp, it->c_str());
		argv[i+1] = temp;
    it++;
	}
  argv[size-1] = NULL;

}


//////////////////////////////////////////////////////////////////////////////////////
//Function takes a function name and match it against a built in command to run.
//Input:  A command name
//Output: None
bool Command::run_built_in_command(string command)
{
  string cmd = command;
  bool flag = false;

  //comment command
  if( cmd=="#" )
  {
    //nothing happens
    flag = true;
  }

  //Changing the prompt
  if( cmd=="setprompt" )
  {
    prompt = arguments.front();
    flag = true;
  }

  //Turning on/off the Debug
  if( cmd=="debug" )
  {
    if (arguments.front()=="on")
    	debug = true;
    if (arguments.front()=="off")
    	debug = false;
    flag = true;
  }

  //Changing Directory
  if( cmd=="chdir" )
  {
  	string temp = arguments.front();
  	char * directory = new char[temp.size()+1];
  	strcpy (directory, temp.c_str());

  	int result = chdir(directory);
  	if (result != 0)
  	{
  		cout << "Problem with changing directory." << endl;;
  	}
  	flag = true;
  }

  //List Current Directory
  if( cmd=="dir" )
  {	
    cout << "Directory Listing: " << get_current_dir_name() << endl;
    flag = true;
  }

  //quit command
  if( cmd=="quit" )
  {
    flag = true;
    quit = true;
  }

  //Parse error
  if (cmd=="PARSE_ERROR")
  {
    cout << "Parse error: " << arguments.front() << endl;
    flag = true;
    quit = true;
  }

  return flag;
}

//////////////////////////////////////////////////////////////////////////////////////
//Function will fork a new process and run the arguments held in argv and argc.
//Input:  None
//Output: None
void Command::run_cmd() {

  prepare_argv(); // prepares argv and argc for execvp()

  pid_t pid;
  int in_file;
  int out_file;

  // Fork our process
  pid = fork();

  // error
  if (pid < 0)
    perror("Error (pid < 0)");

  // child process
  else if (pid == 0)
  {
      // File Redirections
    if(!infile.empty())
    {
      in_file = open(infile.c_str(), O_CREAT | O_RDONLY , S_IREAD | S_IWRITE);
      dup2(in_file, STDIN_FILENO);
      close(in_file);
    }
    if(!outfile.empty())
    {
      out_file = open(outfile.c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
      dup2(out_file, STDOUT_FILENO);
    }

    execvp(argv[0], argv);
    perror("execvp error");

  // parent process
  } else waitpid(pid, NULL, 0);
}

#endif


string Command::to_string()
{
  string s = "Command: ";
  s += name;
  s += "\n";

  string i=1;
  for (list<string>::iterator it = arguments.begin(); it != arguments.end(); ++it)
  {
    s += "Token ";
    s += i;
    s += " ";
    s += *it;
    s += "\n";
    i++;
  }
  
  if (!infile.empty())  s += string(" < ").append(infile);
  s += "\n";
  if (!outfile.empty()) s += string(" > ").append(outfile);
  s += "\n";
  
  return s;
}
