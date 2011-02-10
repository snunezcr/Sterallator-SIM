CC=gcc
CFLAGS=-c -I../include
LINKER=ld
LDFLAGS=-r -lm

PREFIX=field

all: build 

build:
	$(CC) $(CFLAGS) $(PREFIX).c

link:
	$(LINKER) $(LDFLAGS) -o $(PREFIX).o $(PREFIX).o

clean:
	rm -f *.o

