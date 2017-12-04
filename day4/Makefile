CC=g++
#CFLAGS= -std=c++14 -Wall -Wextra -g -Wunreachable-code -Wuninitialized 
CFLAGS= -w -std=c++11
INCLUDE:= -Iinclude/
SOURCE:= $(wildcard *.cpp)

EXE=main.out

all: clean $(EXE)

$(EXE):
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCE) -o $(EXE)
		./main.out

clean:
	rm -rf $(EXE)
	rm -rf $(EXE).dSYM
