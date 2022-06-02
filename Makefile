#
#			Variable Assigments
#

PROJECT_NAME = output

# Tools
CPP = g++
GDB = gdb
RM = rm
PY = python3
AR = ar rcs

# Sources
SOURCE_CPP_LIB = $(wildcard lib/*.cpp)
SOURCE_CPP = $(wildcard *.cpp)
SOURCE_AR = $(wildcard lib/*.a)

TEST_PATH = $(wildcard test/test.py)

# Option flags
GPP_FLAGS = -Wall -Wextra -pedantic -O3
GDB_FLAGS = $(GPP_FLAGS) -g -ggdb 


#
#			Rules
#

.PHONY: all clean debug test lib 

all: $(SOURCE_CPP:.c=.o)
	$(CPP) -o $(PROJECT_NAME) $^ -L. lib/*.a
clean: 
	$(RM) -f *.o lib/*.o lib/*.a
debug: debug.out
	$(GDB) --args $< a.out
test:
	$(PY) $(TEST_PATH)

lib: $(patsubst %.cpp, %.a, $(SOURCE_CPP_LIB))

debug.out:
	$(CPP) $(GDB_FLAGS) -o $@ $(SOURCE_CPP)

%.a: %.o
	$(AR) $@ $^
%.o: $.cpp
	$(CPP) $(GPP_FLAGS) -c -o $@ $^
