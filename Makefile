CC = g++
CFLAGS += -ansi -pedantic -Wall -Werror

inlinecgi: main.cc parser.cc parser.hh
	$(CC) $(CFLAGS) -o inlinecgi main.cc parser.cc
