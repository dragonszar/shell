//////////////////////////////////////////////////////////////////////////////////////
//Function Prototypes
bool is_built_in_command(char * command);   //Determines if command is a built in type
void run_built_in_command(char * command);  //Perfoms the Built-In command
void run_user_command(char * command);      //Running user command
void debug(struct command command)



//////////////////////////////////////////////////////////////////////////////////////
//Struct Declarations

struct command {      //struct for the a single command
  char *command;
  char *argument[];
  char *infile;
  char *outfile;
};


