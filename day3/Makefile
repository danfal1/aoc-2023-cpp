CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -std=c++17 -g

SOURCES = day3.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = day3

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS)
