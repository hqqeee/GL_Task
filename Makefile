#
#			Variable Assigments
#

PROJECT_NAME = dir_test

# Tools
CPP = g++
GDB = gdb
RM = rm
PY = python3

# Sources
SOURCE_C_LIB = $(wildcard lib/*.cpp)
SOURCE_CPP = $(wildcard *.cpp)
SOURCE_AR = $(wildcard lib/*.a)

TEST_PATH = $(wildcard test/test.py)

# Option flags
GPP_FLAGS = -Wall -Wextra -pedantic -O3
GDB_FLAGS = $(GPP_FLAGS) -g -ggdb 


#
#			Rules
#

.PHONY: all, clean, debug, test

all: $(SOURCE_CPP)
	$(CPP) $(GPP_FLAGS) -o $(PROJECT_NAME).o $^
clean: 
	$(RM) -f *.o
debug: debug.o
	$(GDB) $<
test:
	$(PY) $(TEST_PATH)


debug.o:
	$(CPP) $(GDB_FLAGS) -o $@ $(SOURCE_CPP)
