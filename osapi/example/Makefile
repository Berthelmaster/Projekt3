# Quick and dirty (does not handle changes in h-file)
SRCS=main.cpp KeyBoardInput.cpp LogSystem.cpp
OBJS=$(SRCS:.cpp=.o)
BASEPATH=..
# Determine whether this is a debug build or not
ifdef DEBUG
CXXFLAGS=-ggdb -O0
LIBPATH=$(BASEPATH)/lib/host/debug
else
CXXFLAGS=-O2
LIBPATH=$(BASEPATH)/lib/host/release
endif
# Setup the CFLAGS to ensure that the relevant warnings, includes and defines.
CXXFLAGS+=-Wall -D_REENTRANT -DOS_LINUX -I$(BASEPATH)/inc

#%.o : %cpp
#	g++ $(CXXFLAGS) -c -o $@ $^
# Then again, note how the flags are NOT part of the linking process
main: $(OBJS)
	g++ -o main $(OBJS)  -L$(LIBPATH) -lOSApi -lrt -lpthread

all: main

clean:$(OBJS)
	rm -f *.o main
