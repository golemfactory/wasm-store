CFLAGS=-g -Wall -Werror
SOURCES=sha1solver.c sha1.c
BINARY=sha1solver

.FORCE: test
all:
	make test

clean:
	rm -rf *.o $(BINARY) infile out.txt

compile:
	$(CC) $(CFLAGS) -o $(BINARY) $(SOURCES)

test: compile
	printf "abc" > infile
	./$(BINARY) 0 1 2 3 9d infile out.txt	
	cat out.txt
	./$(BINARY) 0 2 2 3 9d infile out.txt
	cat out.txt
	./$(BINARY) 1 2 2 3 9d infile out.txt
	cat out.txt
	rm -f infile out.txt
