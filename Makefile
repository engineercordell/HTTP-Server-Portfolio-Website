CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -g
SRC_DIR := src
BUILD_DIR := build
TARGET := server

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Default build is "server"
all: $(TARGET)

# "server" requires .o files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./server

# clean up build files without removing dir
clean:
	rm -rf $(BUILD_DIR)/* $(TARGET)