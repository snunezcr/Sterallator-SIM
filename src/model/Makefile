CC=gcc
CFLAGS=-c -fPIC -I../include
LINKER=ld
LDFLAGS=-r

PREFIX=model
MACH=machine
MOD=module

STAGEDIR=../lib

all: mach mod link stage

mach:
	$(CC) $(CFLAGS) $(MACH).c

mod:
	$(CC) $(CFLAGS) $(MOD).c

link:
	$(LINKER) $(LDFLAGS) -o $(PREFIX).o $(MACH).o $(MOD).o

stage:
	cp $(PREFIX).o $(STAGEDIR)

clean:
	rm -f $(MACH).o
	rm -f $(MOD).o
	rm -f $(PREFIX).o
	rm -f $(STAGEDIR)/$(PREFIX).o

