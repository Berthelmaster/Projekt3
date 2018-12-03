#Making for host
#> make ARCH=host
ifeq ($(ARCH),host)
CXX=g++
BUILD_DIR=build/host
EXE_DIR=bin/host
MKDIR=mkdir -p
endif

#Making for target
#> make ARCH=target
ifeq ($(ARCH),target)
CXX=arm-rpizw-g++
BUILD_DIR=build/target
EXE_DIR=bin/target
MKDIR=mkdir -p
endif

SOURCES=SetTime.cpp
OBJECTS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.d))
EXE=prog
CXXFLAGS=-I. -pthread

.PHONY: clean all

all: $(EXE)

$(EXE): $(DEPS) $(OBJECTS)
	$(MKDIR) $(EXE_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXE_DIR)/$@ $(OBJECTS)

$(BUILD_DIR)/%.d: %.cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) -MT $(addprefix $(BUILD_DIR)/,$(@:.d=.o)) -MM $(CXXFLAGS) $^ > $@

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) -c -o $@ $^

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

clean:
	rm -rf bin/
	rm -rf build/

help:
	@echo "all: Compiles your program\n"
	@echo "clean: Removes all objects files & the executable\n"
	@echo "help: Prints a list of avaiable targets\n"
