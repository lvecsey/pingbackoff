
CC=gcc

CFLAGS=-O3 -Wall -g -pg

pingbackoff : pingbackoff.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)
