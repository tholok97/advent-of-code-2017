# Makefile for all days
# NOTE: I'm still learning gnu make, so this stuff isn't optimal. 
# (jeg jørs på det)

CC=g++
CFLAGS= -w -std=c++14
INCLUDE= -Iinclude/

DAYDIRS=$(sort $(wildcard day*))
DAYEXES=$(patsubst day%,bin/day%.out,$(DAYDIRS))
DAYNUMS=$(patsubst day%,%,$(DAYDIRS))

all: $(DAYNUMS)

%: bin/day%.out
	$(info ############################################## RUNNING $<)
	$<

bin/day%.out: day%/*.cpp
	$(info ############################################## BUILDING $@)
	$(CC) $(CFLAGS) $(INCLUDE) $(wildcard $<) -o $@

clean:
	rm -f $(DAYEXES)

.PHONY: clean
.SECONDARY:
