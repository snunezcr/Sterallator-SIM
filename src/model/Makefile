CC=gcc
CFLAGS=-c -I../include
LINKER=ld
LDFLAGS=-r

PREFIX=model
MACH=machine
MOD=module

all: mach mod link

mach:
	$(CC) $(CFLAGS) $(MACH).c

mod:
	$(CC) $(CFLAGS) $(MOD).c

link:
	$(LINKER) $(LDFLAGS) -o $(PREFIX).o $(MACH).o $(MOD).o

clean:
	rm -f *.o

