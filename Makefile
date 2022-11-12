SRC_DIR := source
TEST_DIR := test
INC_DIR := include

# all src files
ALLSRC := $(wildcard $(SRC_DIR)/*.cpp)
SRC += $(filter-out $(SRC_DIR)/LexicalAnalyzer.cpp $(SRC_DIR)/StupidCompiler.cpp $(SRC_DIR)/SyntaxAnalyzer.cpp $(SRC_DIR)/lexical.cpp $(SRC_DIR)/syntax.cpp, $(ALLSRC))
# test src files
TESTSRC += $(filter-out $(SRC_DIR)/main.cpp, $(SRC)) $(wildcard $(TEST_DIR)/*.cpp)
# C++ compiler
CC := g++
# CPP PreProcessor Flag
CPPFLAGS := -I $(INC_DIR)
# Compiler flags
CFLAGS := -g

default:all

all: lexical syntax

lexical: $(SRC) $(SRC_DIR)/lexical.cpp 
		$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

syntax: $(SRC_DIR)/syntax.cpp
		$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

test: $(TESTSRC)
		$(CC) $(CPPFLAGS) $(CFLAGS)  $^ -o $@
		./test.exe

clean:
	del *.exe
	del *.txt

run:
	.\lexical.exe
	.\syntax.exe

.PHONY: clean all run