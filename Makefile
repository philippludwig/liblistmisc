c_flags = -std=c99 -Wall -Wextra -pedantic
libs = -lm
prefix = /usr/local

# By default, a shared library is being built.
all: shared
	

shared: c_flags += -fPIC -O2
shared: compile
shared: build-shared

shared-debug: c_flags += -fPIC -O0 -g
shared-debug: compile
shared-debug: build-shared


static: c_flags += -O2
static: compile
static: build-static

static-debug: c_flags += -O0 -g
static-debug: compile
static-debug: build-static

# Helper target for compiling the library
compile:
	gcc $(c_flags) -c listmisc.c

# Helper target for building the shared library
build-shared:
	gcc -shared -o liblistmisc.so listmisc.o

# Helper target for building the static library
build-static:
	ar rcs liblistmisc.a listmisc.o
	
# Additional targets for cleaning and installing
clean:
	rm -fv list.o

distclean:
	rm -fv list.o liblistmisc.so liblistmisc.a

install:
	mkdir -p $(prefix)/lib/
	mkdir -p $(prefix)/include/
	-@[ -e liblistmisc.so ] && cp -v liblistmisc.so $(prefix)/lib/ | true
	cp -v listmisc.h $(prefix)/include/listmisc.h

uninstall:
	rm -fv $(prefix)/lib/liblistmisc.so
	rm -rf $(prefix)/include/listmisc.h
