CC=gcc
AR=ar
LD=ld

STAGEDIR=lib

MODEL=model
FIELD=field
UTIL=log

SHCORE=libcore.so.1
SHCOREVER=0.1
SHLDFLAGS=-lc

STCORE=libcore
STLDFLAGS=-lc -lm

all: staging library shared static sweep

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

clean:
	make -C util clean
	make -C model clean
	make -C field clean
	rm -rf $(STAGEDIR)

