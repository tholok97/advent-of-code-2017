# Makefile for all days
# NOTE: I'm still learning gnu make, so this stuff isn't optimal. 
# (jeg jørs på det)

CC=g++
#CFLAGS= -std=c++14 -Wall -Wextra -g -Wunreachable-code -Wuninitialized 
CFLAGS= -w -std=c++11
INCLUDE:= -Iinclude/

EXE=main.out

all: 1 2 3 4 5

1:
	$(info --------------------- DAY 1 ---------------------)
	@$(CC) $(CFLAGS) $(INCLUDE) $(wildcard day1/*.cpp) -o day1/$(EXE)
	@day1/$(EXE)

2:
	$(info --------------------- DAY 2 ---------------------)
	@$(CC) $(CFLAGS) $(INCLUDE) $(wildcard day2/*.cpp) -o day2/$(EXE)
	@day2/$(EXE)

3:
	$(info --------------------- DAY 3 ---------------------)
	@$(CC) $(CFLAGS) $(INCLUDE) $(wildcard day3/*.cpp) -o day3/$(EXE)
	@day3/$(EXE)

4:
	$(info --------------------- DAY 4 ---------------------)
	@$(CC) $(CFLAGS) $(INCLUDE) $(wildcard day4/*.cpp) -o day4/$(EXE)
	@day4/$(EXE)

5:
	$(info --------------------- DAY 5 ---------------------)
	@$(CC) $(CFLAGS) $(INCLUDE) $(wildcard day5/*.cpp) -o day5/$(EXE)
	@day5/$(EXE)

clean:
	rm -rf $(wildcard day*/$(EXE))
	rm -rf $(wildcard day*/$(EXE).dSYM)
