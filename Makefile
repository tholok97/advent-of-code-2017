# Makefile for all days
# NOTE: I'm still learning gnu make, so this stuff is probably not optimal. 
# (jeg jørs på det)

CC=g++
CFLAGS= -w -std=c++14
INCLUDE= -Iinclude/

DAYCPPS=$(sort $(wildcard day*.cpp))
DAYEXES=$(patsubst day%.cpp,bin/day%.out,$(DAYCPPS))
DAYNUMS=$(patsubst day%.cpp,%,$(DAYCPPS))

all: $(DAYEXES)

%: bin/%.out
	$(info ############################################## RUNNING $<)
	$<

bin/%.out: %.cpp
	$(info ############################################## BUILDING $@)
	$(CC) $(CFLAGS) $(INCLUDE) $(wildcard $<) -o $@

clean:
	rm -f $(DAYEXES)

.PHONY: clean
.SECONDARY:
