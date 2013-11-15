PROGRAM=ioshell

ShellSource=shell.cpp
ShellOut=shell.o

CmdSource=command.h
CmdOut=command.o

ScanSource=scanner.cpp
ScanOut=scanner.o

FlexIn=lex.yy.txt
FlexOut=lex.yy.c


run: all
	./$(PROGRAM)

all: $(ShellOut) $(ScanOut) $(CmdOut)
	g++ $(CmdOut) $(ShellOut) -lfl -o $(PROGRAM)
	# -lfl loads flex libraries so ScanOut links properly.

$(ShellOut): $(ShellSource)
	g++ -c $(ShellSource)

$(CmdOut): $(CmdSource)
	g++ -c $(CmdSource)

$(ScanOut): $(FlexOut) $(ScanSource)
	g++ -c $(ScanSource)

$(FlexOut): $(FlexIn)
	flex -o $(FlexOut) $(FlexIn)


clean:
	rm $(FlexOut) $(PROGRAM) *.o


scans: $(ScanOut) scanstub.cpp
	g++ scanstub.cpp -lfl -o scans
	./scans