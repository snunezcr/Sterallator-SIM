CC=gcc
CFLAGS=-I../include
LINKER=ld
LDFLAGS=-lm

TESTPOINT=test_point
STAGEDIR=../lib
BINDIR=../bin
CORELIB=libcore.a

all: build stage

build:
	$(CC) -o $(TESTPOINT) $(CFLAGS) $(TESTPOINT).c $(STAGEDIR)/$(CORELIB) $(LDFLAGS)

stage:
	cp $(TESTPOINT) $(BINDIR)

clean:
	rm -f $(TESTPOINT)
	rm -f $(BINDIR)/$(TESTPOINT)

