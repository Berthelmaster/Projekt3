# What you set
SRC=traadkommunikationtest.cpp ConvertToGram.cpp UART.cpp Messages.cpp T1_webApp.cpp T2_coffeeOrderHandler.cpp T3_localUI.cpp T4_timeSetting.cpp MsgQueue.cpp
# Name of your exe file
EXE_NAME=main
# Path to where UWS source is
UWSPATH=..


OBJS=$(addprefix ${OBJ_DEST_DIR}/,$(notdir ${SRC:%.cpp=%.o}))
DEPS=$(addprefix ${OBJ_DEST_DIR}/,$(notdir ${SRC:%.cpp=%.d}))


# Which target? set default
ifndef TARGET
TARGET=host
endif

# Debug build? debug is default
ifdef DEBUG
CXXFLAGS=-g -I. -std=c++17
MODE=debug
else
CXXFLAGS=-O2 -I. -Isrc -std=c++17
MODE=release
endif
DEST_DIR=bin/${TARGET}/${MODE}
OBJ_DEST_DIR=build/${TARGET}/${MODE}

UWSLIBPATH=${UWSPATH}/lib/${TARGET}/${MODE}
LDFLAGS=-L$(UWSLIBPATH) -luWS -lssl -lcrypto -lz -lrt -lpthread -lOSApi



ifeq (${TARGET},host)
# Include host specific stuff
include compiler_setup.host
endif

ifeq (${TARGET},rpi)
CXX=arm-rpizw-g++
BUILD_DIR=build/target
EXE_DIR=bin/target
endif

# Setting compiler flags
CXXFLAGS+= -Wall -D_REENTRANT -DOS_LINUX -Iinc -I${UWSPATH} -I${UWSPATH}/inc

VPATH=src

all: info ${DEST_DIR}/${EXE_NAME}

info:
	@echo "Compiling for '${TARGET}' in '${MODE}' mode..."

${OBJ_DEST_DIR}/%.o: %.cpp
	@echo "Compiling "$<
	@${CXX} -c $< -o $@ ${CXXFLAGS}

${OBJ_DEST_DIR}/%.d: %.cpp
	@echo "Generating dependency for $<"
	@mkdir -p ${OBJ_DEST_DIR}
	@$(CXX) -MT${OBJ_DEST_DIR}/$(@:.d=.o) -MM $(CXXFLAGS) $^ > $@

${DEST_DIR}:
	@mkdir -p ${DEST_DIR}

${OBJ_DEST_DIR}:
	@mkdir -p ${OBJ_DEST_DIR}

${DEST_DIR}/${EXE_NAME}: ${OBJ_DEST_DIR} ${DEST_DIR} $(DEPS) ${OBJS}
	@echo "Linking '"${EXE_NAME}"'"
	@$(CXX) -o $@ $(OBJS) ${LDFLAGS}


clean:
	@echo "Cleaning up..."
	@rm -f ${DEST_DIR}/${EXE_NAME} $(OBJS) $(DEPS)

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif
