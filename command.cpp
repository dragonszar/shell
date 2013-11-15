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
    void prepare_argv();
    void run_cmd();
    string to_string();


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
  if (debug) cout << to_string() << endl;
	
  if( run_built_in_command(name) != true)
  {
  	run_cmd();
  }   
}

string Command::to_string()
{
  string s = "Command: ";
  s += name;

  for (list<string>::iterator it = arguments.begin(); it != arguments.end(); ++it)
  {
    s += " ";
    s += *it;
  }
  
  if (!infile.empty())  s += string(" < ").append(infile);
  if (!outfile.empty()) s += string(" > ").append(outfile);
  return s;
}

void Command::prepare_argv()
{
	list<string> tempargs;
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

// this will fork a new process and run the arguments held in argv and argc.
// Thanks to http://tldp.org/LDP/lpg/node11.html for their tutorial on pipes
// in C, which allowed me to handle user input with ampersands.
void Command::run_cmd() {
  prepare_argv(); // prepares argv and argc for exec()

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
  } else if (!found_amp)
    waitpid(pid, NULL, 0); // only wait if no ampersand
}

#endif
