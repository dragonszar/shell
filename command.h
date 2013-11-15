#include <string>
#include <iostream>
#include <cstring>
#include <list>
#include <unistd.h>

using namespace std;

class Command
{
public:
    Command (string);
    ~Command ();
    bool execute();
    void run_built_in_command(string command);


    static string prompt;
    static bool debug;
    static bool quit;
    string name;
    list<string> arguments;
    string infile;
    string outfile;
};

string Command::prompt =  "iosh% ";
bool Command::debug = false;
bool Command::quit = false;

// Constructor
Command::Command (string n) { name = n; }
Command::~Command () {}


// Executing the command
bool Command::execute() 
{ 
	if(debug == true)
	{
		//print out the tokenss
	}
    run_built_in_command(name);
    return true; 
   

	return false;
}


//////////////////////////////////////////////////////////////////////////////////////
//Function handles  built in commands
//Input:  A build in command
//Output: None
void Command::run_built_in_command(string command)
{
  string cmd = command;
  
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