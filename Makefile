#
# Makefile that builds btest
# 
CC = gcc
CFLAGS = -O -Wall -m32
LIBS = -lm

all: btest

btest: btest.c src/*.c decl.c tests.c btest.h bits.h
	$(CC) $(CFLAGS) $(LIBS) -o btest src/*.c btest.c decl.c tests.c

clean:
	rm -f *.o btest *~


