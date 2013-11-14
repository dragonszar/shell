PROGRAM=scanner

FlexOut=scanner.c
FlexIn=scanner.lex
ScannerObj=scanner.o

run: all
	./$(PROGRAM)

all: scanner

scanner: $(ScannerObj)
	g++ $(ScannerObj) -lfl -o $(PROGRAM)

scanner.o:
	flex -o $(FlexOut) $(FlexIn)
	g++ -c $(FlexOut)

clean:
	rm *.o $(PROGRAM)
	rm $(FlexOut)
