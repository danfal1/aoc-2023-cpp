#pragma once

#include <functional>
#include <vector>
#include <string>

typedef std::vector<std::vector<char>> Schema;

struct Symbol {
    unsigned x;
    unsigned y;
    char c;

    bool operator==(const Symbol& other) const {
        return x == other.x && y == other.y && c == other.c;
    }
};

template<> struct std::hash<Symbol> {
    std::size_t operator()(const Symbol& s) const {
        std::size_t h1 = std::hash<unsigned>{}(s.x);
        std::size_t h2 = std::hash<unsigned>{}(s.y);
        return h1 ^ (h2 << 1);
    }
};

struct Number {
    std::string str;
    Symbol symbol;
};

