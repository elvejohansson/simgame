TARGET := simgame

CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11

.PHONY: run
run: $(TARGET)
	./$(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
