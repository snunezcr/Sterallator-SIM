CC=gcc
CFLAGS=-c -fPIC -I../include
LINKER=ld
LDFLAGS=-r -lm

PREFIX=field
STAGEDIR=../lib

all: build stage

build:
	$(CC) $(CFLAGS) $(PREFIX).c

link:
	$(LINKER) $(LDFLAGS) -o $(PREFIX).o $(PREFIX).o

stage:
	cp $(PREFIX).o $(STAGEDIR)

clean:
	rm -f $(PREFIX).o
	rm -f $(STAGEDIR)/$(PREFIX).o

