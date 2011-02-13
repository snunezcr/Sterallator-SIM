CC=gcc
AR=ar
LD=ld

STAGEDIR=lib
BINDIR=bin

MODEL=model
FIELD=field
UTIL=log

SHCORE=libcore.so.1
SHCOREVER=0.1
SHLDFLAGS=-lc

STCORE=libcore
STLDFLAGS=-lc -lm

all: staging library shared static sweep binaries

staging:
	mkdir -p $(STAGEDIR)

library:
	make -C util
	make -C model
	make -C field

shared:
	$(CC) -shared \
	-o $(STAGEDIR)/$(SHCORE).$(SHCOREVER) \
	$(STAGEDIR)/$(UTIL).o \
	$(STAGEDIR)/$(MODEL).o \
	$(STAGEDIR)/$(FIELD).o \
	$(SHLDFLAGS)

static:
	$(LD) -r \
		-o $(STAGEDIR)/$(STCORE).o \
		$(STAGEDIR)/$(UTIL).o \
		$(STAGEDIR)/$(MODEL).o \
		$(STAGEDIR)/$(FIELD).o
	$(AR) rcs $(STAGEDIR)/$(STCORE).a $(STAGEDIR)/$(STCORE).o
	
sweep:
	rm -f $(STAGEDIR)/*.o

binaries:
	mkdir -p $(BINDIR) 
	make -C testing

clean:
	make -C util clean
	make -C model clean
	make -C field clean
	make -C testing clean
	rm -rf $(STAGEDIR)
	rm -rf $(BINDIR)

