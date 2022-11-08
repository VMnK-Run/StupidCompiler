SRC_DIR := source
TEST_DIR := test
INC_DIR := include

# all src files
ALLSRC := $(wildcard $(SRC_DIR)/*.cpp)
SRC += $(filter-out $(SRC_DIR)/main.cpp $(SRC_DIR)/lexical.cpp $(SRC_DIR)/syntax.cpp, $(ALLSRC))
# test src files
TESTSRC += $(filter-out $(SRC_DIR)/main.cpp, $(SRC)) $(wildcard $(TEST_DIR)/*.cpp)
# C++ compiler
CC := g++
# CPP PreProcessor Flag
CPPFLAGS := -I $(INC_DIR)
# Compiler flags
CFLAGS := -g

default: all
all: lexical syntax

main: $(SRC) $(SRC_DIR)/main.cpp
		$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@


lexical: $(SRC) $(SRC_DIR)/lexical.cpp
		$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@


syntax: $(SRC) $(SRC_DIR)/syntax.cpp
		$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

test: $(TESTSRC)
		$(CC) $(CPPFLAGS) $(CFLAGS)  $^ -o $@
		./test.exe

clean:
	del *.exe
	del *.txt

lexical-save:
	.\lexical.exe > lexical.txt

run:
	.\lexical.exe > lexical.txt
	.\syntax.exe

.PHONY: clean all main run