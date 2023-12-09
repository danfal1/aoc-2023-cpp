CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -std=c++17 -g

SOURCES = day4.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = day4

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS)
