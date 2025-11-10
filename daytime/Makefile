CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = client

$(TARGET): client.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) client.cpp

clean:
	rm -f $(TARGET)

.PHONY: clean
