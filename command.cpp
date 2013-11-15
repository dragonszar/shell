#ifndef COMMAND_CPP
#define COMMAND_CPP

#include <string>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cerrno>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <list>
#include <unistd.h>

using namespace std;

class Command
{
public:
    Command (string);
    ~Command ();
    Command (string n, list<string> arg, string in, string out);
    void execute();
    bool run_built_in_command(string command);
    void run_debug();
    void run_cmd(int argc, char** argv);


    static string prompt;
    static bool debug;
    static bool quit;
    string name;
    list<string> arguments;
    string infile;
    string outfile;
    char** argv;
    int argc;
};

string Command::prompt =  "iosh% ";
bool Command::debug = false;
bool Command::quit = false;

// Constructor
Command::Command (string n) { name = n; }
Command::~Command () {}
Command::Command (string n, list<string> arg, string in, string out) 
{ 
	name = n; 
	arguments = arg;
	infile = in;
	outfile = out;
}


// Executing the command
void Command::execute() 
{ 
	run_debug();
	
    if( run_built_in_command(name) != true)
    {
    	run_cmd(argc, argv);
    }   
}

void Command::run_debug()
{
	list<string> tempargs;
	int size = arguments.size();
	char* temp = new char[name.size()+1];
	strcpy (temp,name.c_str());

	argc = size+1;
	argv = new char*[argc];
	argv[0] = temp;


	cout << "Command: " << name << endl;

	for (int i=0; i<size; i++)
	{
		string currentarg = arguments.front();
		if (debug == true)
			cout << "Token " << i << ": " << currentarg << endl;
		arguments.pop_front();
		tempargs.push_back(currentarg);

		temp = new char[currentarg.size()+1];
		strcpy (temp,currentarg.c_str());
		argv[i+1] = temp;
	}
	arguments = tempargs;
}


//////////////////////////////////////////////////////////////////////////////////////
//Function handles  built in commands
//Input:  A build in command
//Output: None
bool Command::run_built_in_command(string command)
{
  string cmd = command;
  bool flag = false;

  if( cmd=="#" )
  {
    //nothing happens
    flag = true;
  }

  if( cmd=="setprompt" )
  {
    prompt = arguments.front();
    flag = true;
  }

  if( cmd=="debug" )
  {
    //do something about the debug
    if (arguments.front()=="on")
    	debug = true;
    if (arguments.front()=="off")
    	debug = false;
    flag = true;
  }

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

  if (cmd=="PARSE_ERROR")
  {
    cout << "Parse error: " << arguments.front() << endl;
    flag = true;
    quit = true;
  }

  return flag;
}

// Given the number of arguments (argc) and an array of arguments (argv),
// this will fork a new process and run those arguments.
// Thanks to http://tldp.org/LDP/lpg/node11.html for their tutorial on pipes
// in C, which allowed me to handle user input with ampersands.
void Command::run_cmd(int argc, char** argv) {
  pid_t pid;
  const char *amp;
  amp = "&";
  bool found_amp = false;
  
  // If we find an ampersand as the last argument, set a flag.
  if (strcmp(argv[argc-1], amp) == 0)
    found_amp = true;

  // Fork our process
  pid = fork();
  
  // error
  if (pid < 0)
    perror("Error (pid < 0)");
  
  // child process
  else if (pid == 0) {
    // If the last argument is an ampersand, that's a special flag that we
    // don't want to pass on as one of the arguments.  Catch it and remove
    // it here.
    if (found_amp) {
      argv[argc-1] = NULL;
      argc--;
    }

    execvp(argv[0], argv);
    perror("execvp error");

  // parent process
  } else if (!found_amp)
    waitpid(pid, NULL, 0); // only wait if no ampersand
}

#endif