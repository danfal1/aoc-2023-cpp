CXX = clang++-17
CXXFLAGS = -Wall -Werror -pedantic -std=c++17

SOURCES = day1.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = day1

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS)
