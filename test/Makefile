SRC_DIR := ../source
INC_DIR := ../include

# all src files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
TESTSRC += $(filter-out $(SRC_DIR)/main.cpp, $(SRC)) $(wildcard *.cpp)
# C++ compiler
CC := g++
# CPP PreProcessor Flag
CPPFLAGS := -I $(INC_DIR)
# Compiler flags
CFLAGS := -g -Wall

default: test

test: $(TESTSRC)
		$(CC) $(CPPFLAGS) $(CFLAGS) -Werror $^ -o $@
		./test.exe

clean:
	del *.exe 

.PHONY: clean all