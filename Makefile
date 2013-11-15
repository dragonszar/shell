PROGRAM=ioshell

FlexIn=scanner.lex
FlexOut=scanner.cpp
ScanOut=scanner.o

ShellOut=shell.o
ShellSource=shell.cpp

CmdObj=command.o
CmdSource=command.h


run: all
	./$(PROGRAM)

all: $(ShellOut) $(ScanOut) $(CmdOut)
	g++ $(CmdOut) $(ScanOut) $(ShellOut) -lfl -o $(PROGRAM)

$(ScanOut): $(FlexIn)
	flex -o $(FlexOut) $(FlexIn)
	g++ -c $(FlexOut)

$(CmdOut): $(CmdSource)
	g++ -c $(CmdSource)

$(ShellOut): $(ShellSource)
	g++ -c $(ShellSource)

clean:
	rm *.o $(PROGRAM)
	rm $(FlexOut)
