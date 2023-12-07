CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -std=c++17 -g

SOURCES = day2.cpp lexer.cpp parser.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = day2

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS)
