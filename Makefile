SRC_DIR := source
OBJ_DIR := target
INC_DIR := include

# all src files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
# all objects
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
# C++ compiler
CC := g++
# CPP PreProcessor Flag
CPPFLAGS := -I $(INC_DIR)
# Compiler flags
CFLAGS := -g -Wall

default: all
all: main

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

main: $(OBJ)
		$(CC) -Werror $^ -o $@

$(OBJ_DIR):
	mkdir $@

clean:
	del *.exe 
	del $(OBJ_DIR)\*.o

.PHONY: clean all