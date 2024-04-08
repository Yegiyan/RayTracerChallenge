# Compiler settings
CXX := g++
CXXFLAGS := -Wall -g
LDFLAGS :=

# Project settings
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .

# Automatically include all source files from the SRC_DIR
SOURCES := $(wildcard ../$(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET := $(BIN_DIR)/program

# Default target
all: $(TARGET)

# Linking all the object files to create the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Compiling each source file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	$(RM) -r $(OBJ_DIR) $(TARGET)

.PHONY: all clean
