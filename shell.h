//////////////////////////////////////////////////////////////////////////////////////
//Function Prototypes
bool is_built_in_command(char * command);   //Determines if command is a built in type
void run_built_in_command(char * command);  //Perfoms the Built-In command
void run_user_command(char * command);      //Running user command
void debug(struct command command)



//////////////////////////////////////////////////////////////////////////////////////
//Struct Declarations

struct command {    // represents a single command to be exec'ed
  char *command;
  char *argument[];
  char *infile;
  char *outfile;
};

struct Token    // represents the tokens parsed by flex
{
    int type; // 1=word, 2=string, 3=meta, 4=comment, 0=end
    char *string;
};


