
# Quick and dirty (does not handle changes in h-file)
SRCS=traadkommunikationtest.cpp ConvertToGram.cpp UART.cpp Messages.cpp T1_webApp.cpp T2_coffeeOrderHandler.cpp T3_localUI.cpp T4_timeSetting.cpp
OBJS=$(SRCS:.cpp=.o)
DEPS=${SRCS:.cpp=.d}
BASEPATH=..
# Determine whether this is a debug build or not
ifdef DEBUG
CXXFLAGS=-ggdb -O0
LIBPATH=$(BASEPATH)/lib/host/debug
else
CXXFLAGS=-O2
LIBPATH=$(BASEPATH)/lib/host/release
endif

ifeq (${ARCH},host)
CXX=g++
BUILD_DIR=build/host
EXE_DIR=bin/host
endif

ifeq (${ARCH},target)
CXX=arm-rpizw-g++
BUILD_DIR=build/target
EXE_DIR=bin/target
endif
# Setup the CFLAGS to ensure that the relevant warnings, includes and defines.
CXXFLAGS+=-Wall -D_REENTRANT -DOS_LINUX -I$(BASEPATH)/inc

#%.o : %cpp
#	g++ $(CXXFLAGS) -c -o $@ $^
# Then again, note how the flags are NOT part of the linking process
main: $(OBJS)
	${CXX} -o main $(OBJS)  -L$(LIBPATH) -lOSApi -lrt -lpthread


${BUILD_DIR}/%.d: %.cpp
	${CXX} -MT ${addprefix ${BUILD_DIR}/,${@:.d=.o}} -MM ${CXXFLAGS} $^ > $@

all: main

clean:$(OBJS)
	rm -f *.o main
