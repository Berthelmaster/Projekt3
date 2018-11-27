# Quick and ok!

# Which target? set default
ifndef TARGET
TARGET=host
endif

# Debug build? debug is default
ifdef DEBUG
CXXFLAGS=-g
DEST_DIR=lib/${TARGET}/debug
MODE=debug
else
CXXFLAGS=-O2
DEST_DIR=lib/${TARGET}/release
MODE=release
endif
OBJ_DEST_DIR=build/${DEST_DIR}


COMMON=$(addprefix common/,Time.cpp Timer.cpp LogSystem.cpp LogOutputStdOut.cpp LogTypes.cpp Log.cpp Completion.cpp)
LINUX=$(addprefix linux/,ClockTime.cpp Mutex.cpp Conditional.cpp Thread.cpp ThreadFunctor.cpp Semaphore.cpp Utility.cpp)
SRC=${COMMON} ${LINUX}
OBJS=$(addprefix ${OBJ_DEST_DIR}/,$(notdir ${SRC:%.cpp=%.o}))
DEPS=$(addprefix ${OBJ_DEST_DIR}/,$(notdir ${SRC:%.cpp=%.d}))

ifeq (${TARGET},host)
# Include host specific stuff
include compiler_setup.host
endif

ifeq (${TARGET},target)
# Include target specific stuff
include compiler_setup.target
endif

# Setting compiler flags
CXXFLAGS+= -Wall -Iinc  -D${OS}
VPATH=common linux

all: info ${DEST_DIR}/libOSApi.a

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

${DEST_DIR}/libOSApi.a: ${OBJ_DEST_DIR} ${DEST_DIR} $(DEPS) ${OBJS} 
	@echo "Linking "$<
	@${AR} cr $@ ${OBJS}


clean:
	@echo "Cleaning up..."
	@rm -f ${DEST_DIR}/libOSApi.a $(OBJS) $(DEPS)

-include $(DEPS)
