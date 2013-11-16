PROGRAM=ioshell

ShellSource=shell.cpp
ShellOut=shell.o

CmdSource=command.cpp
CmdOut=command.o

ScanSource=parser.cpp
ScanOut=parser.o

FlexIn=lex.yy.txt
FlexOut=lex.yy.c


run: all
	./$(PROGRAM)

all: $(ShellOut) $(CmdOut) $(ScanOut) $(FlexOut)
	g++ $(ShellOut) -lfl -o $(PROGRAM)

$(ShellOut): $(ShellSource)
	g++ -c $(ShellSource)

$(CmdOut): $(CmdSource)
	g++ -c $(CmdSource)

$(ScanOut): $(FlexOut) $(ScanSource)
	g++ -c $(ScanSource)

flex: $(FlexOut)

$(FlexOut): $(FlexIn)
	flex -o $(FlexOut) $(FlexIn)


clean:
	rm $(PROGRAM) *.o
