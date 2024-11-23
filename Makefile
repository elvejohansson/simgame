TARGET := simgame

CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -Iinclude -I/opt/homebrew/include -Llib

SRC_DIR := src
OUT_DIR := build

SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJS := $(SRCS:‰=$(OUT_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

.PHONY: run
run: $(OUT_DIR)/$(TARGET)
	$(OUT_DIR)/$(TARGET)

$(OUT_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ -lglfw3 -framework OpenGL

$(OUT_DIR)/%.cpp.o: %.cpp
	mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(OUT_DIR)/$(TARGET)
