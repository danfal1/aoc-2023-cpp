CXX = clang++-17
CXXFLAGS = -Wall -Werror -pedantic -std=c++17

SOURCES = day2.cpp lexer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = day2

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS)
