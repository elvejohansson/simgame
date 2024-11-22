TARGET := simgame

CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -Iinclude -I/opt/homebrew/include -Llib

.PHONY: run
run: $(TARGET)
	./$(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET) -lglfw3 -framework OpenGL

.PHONY: clean
clean:
	rm -f $(TARGET)
