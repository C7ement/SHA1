CC=gcc
CFLAGS=-Wextra -pedantic -O3 

PATHOBJ=./obj/
PATHSRC= ./
PATHBIN= ./
OBJ=$(addprefix $(PATHOBJ),testSHA1.o sha1.o sha1opt.o solveHash.o earlyExit.o passwordGenerator.o)

all: main

main: $(OBJ)
	$(CC) -o $(PATHBIN)$@ $^ -lm

$(PATHOBJ)%.o: $(PATHSRC)%.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf $(PATHBIN)main
	rm -rf $(PATHOBJ)*.o

.PHONY: all clean debug
