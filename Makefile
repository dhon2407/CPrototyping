CC = gcc
CFLAGS = -Wall -Wextra \
		 -I./sc/inc

BUILD_DIR = ./build
SRC_DIR = ./sc/src
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR =  $(BUILD_DIR)/bin

# List of source files (without directory)
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Object files derived from source files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# The final executable
EXECUTABLE = $(BIN_DIR)/program

.PHONY: all clean

all: $(EXECUTABLE)
	@echo
	@./$(BIN_DIR)/program

# Linking the object files to create the executable
$(EXECUTABLE): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compiling each source file into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)