CC=gcc

STAGEDIR=lib

MODEL=model
FIELD=field
UTIL=log

SHCORE=libcore.so.1
SHCOREVER=0.1
SHLDFLAGS=-lc

all: staging library shared

staging:
	mkdir -p $(STAGEDIR)

library:
	make -C util
	make -C model
	make -C field

shared:
	$(CC) -shared -Wl,-soname,$(SHCORE) \
	-o $(STAGEDIR)/$(SHCORE).$(SHCOREVER) \
	$(STAGEDIR)/$(UTIL).o \
	$(STAGEDIR)/$(MODEL).o \
	$(STAGEDIR)/$(FIELD).o \
	$(SHLDFLAGS)
	
clean:
	make -C util clean
	make -C model clean
	make -C field clean
	rm -rf $(STAGEDIR)

