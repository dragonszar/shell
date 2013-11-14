#include <string>
#include <list>

using namespace std;

class Command
{
public:
    Command (string);
    ~Command ()

    bool execute ();

    string name;
    list<string> arguments;
    string infile;
    string outfile;
};


// Constructor
Command::Command (string name) { _name = name; }
Command::~Command () {}


// Executing the command
bool Command::execute() { return true; }
