# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN_DIR = bin

# OBJS specifies which files to compile as part of the project
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# CC specifies which compiler we're using
CC = gcc

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I$(INC_DIR) -I/usr/include/SDL2

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L/usr/lib

# COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -Wall -Werror -Wextra -pedantic

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lm

# OBJ_NAME specifies the name of our executable
OBJ_NAME = $(BIN_DIR)/maze

# Default target
all: $(OBJ_NAME)

# Link the object files to create the executable
$(OBJ_NAME): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

# Compile each source file to an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c $< -o $@

# Create directories if they do not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Linux SDL installation
linux_install:
	sudo apt-get install libsdl2-dev

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean linux_install

