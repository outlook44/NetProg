CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = server

$(TARGET): server.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) server.cpp

clean:
	rm -f $(TARGET)

.PHONY: clean
