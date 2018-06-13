CC=gcc
CFLAGS=-Wextra -pedantic -O3 

PATHOBJ=./obj/
PATHSRC= ./
PATHBIN= ./
OBJ=$(addprefix $(PATHOBJ),main.o sha1.o)

all: main

main: $(OBJ)
	$(CC) -o $(PATHBIN)$@ $^ -lm

$(PATHOBJ)%.o: $(PATHSRC)%.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf $(PATHBIN)main
	rm -rf $(PATHOBJ)*.o

.PHONY: all clean debug
