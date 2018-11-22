SOURCES=testuart.cpp UART.cpp
OBJECT=${addprefix ${BUILD_DIR}/,${SOURCES:.cpp=.o}}
EXE=main
DEPS=${addprefix ${BUILD_DIR}/,${SOURCES:.cpp=.d}}
CXXFLAGS=-I.

ifeq (${ARCH},host)
CXX=g++
BUILD_DIR=build/host
EXE_DIR=bin/host
endif

ifeq (${ARCH},rpi)
CXX=arm-rpizw-g++
BUILD_DIR=build/rpi
EXE_DIR=bin/rpi
endif

all: ${EXE}

${EXE}: ${DEPS} ${OBJECT}
	${CXX} ${CXXFLAGS} -o ${EXE_DIR}/$@ ${OBJECT} -lpthread

${BUILD_DIR}/%.o: %.cpp
	${CXX} -c -o $@ $^

${BUILD_DIR}/%.d: %.cpp
	${CXX} -MT ${addprefix ${BUILD_DIR}/,${@:.d=.o}} -MM ${CXXFLAGS} $^ > $@


clean:
	rm -f build/*/*.o build/*/*.d bin/*/${EXE}


help:
	@echo ${EXE}
	@echo main
	@echo part1
	@echo part2
	@echo clean
	@echo all
	@echo help



ifneq (${MAKECMDGOALS},clean)
-include ${DEPS}
endif
