CC=g++
CFLAGS=-c
FLEX=flex
PROGRAM=scanner


run: all
	./$(PROGRAM)

all: scanner

scanner: lex.yy.o
	$(CC) lex.yy.o -lfl -o $(PROGRAM)

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) lex.yy.c

lex.yy.c: scanner.yy
	$(FLEX) scanner.yy

clean:
	rm *o $(PROGRAM)
	rm lex.yy.c
