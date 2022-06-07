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

all: $(patsubst %.cpp, %.o, $(SOURCE_CPP))
	$(CPP) -o $(PROJECT_NAME).out $^ -L. lib/*.a
clean: 
	$(RM) -f *.o lib/*.o lib/*.a *.out ==
debug: dbg.out
	$(GDB) --args $< a.out
test:
	$(PY) $(TEST_PATH)

lib: $(patsubst %.cpp, %.a, $(SOURCE_CPP_LIB))

debug.o: 
	$(CPP) $(GDB_FLAGS) -c -o $@ $(SOURCE_CPP)
dbg.out: debug.o
	$(CPP) -o $@ $^ -L. lib/*.a

%.a: %.o
	$(AR) $@ $^
%.o: $.cpp
	$(CPP) $(GPP_FLAGS) -c -o $@ $^
