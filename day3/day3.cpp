#include "day3.hpp"

#include <cctype>
#include <exception>
#include <fstream>
#include <functional>
#include <numeric>
#include <optional>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

std::ifstream get_file_stream(std::string file_name) {
    std::ifstream ifs(file_name);
    if (!ifs) {
        throw std::runtime_error("failed to open input file");
    }
    return ifs;
}

bool is_special_char(char c) {
    return c != '.' && std::ispunct(c);
}

Symbol make_symbol(char c, unsigned x, unsigned y) {
    return Symbol{x, y, c};
}

std::optional<Symbol> get_symbol(Schema& s, unsigned x, unsigned y) {
    char c;
    if (x > 0) {
        c = s[y][x - 1];
        if (is_special_char(c)) {
            return make_symbol(c, x - 1, y);
        }
    }

    if (x < s[y].size() - 1) {
        c = s[y][x + 1];
        if (is_special_char(c)) {
            return make_symbol(c, x + 1, y);
        }
    }

    if (y > 0) {
        c = s[y - 1][x];
        if (is_special_char(c)) {
            return make_symbol(c, x, y - 1);
        }
    } 

    if (y < s.size() - 1) {
        c = s[y + 1][x];
        if (is_special_char(c)) {
            return make_symbol(c, x, y + 1);
        }
    }

    if (x > 0 && y > 0) {
        c = s[y - 1][x - 1];
        if (is_special_char(c)) {
            return make_symbol(c, x - 1, y - 1);
        }
    }

    if (x < s[y].size() - 1 && y > 0) {
        c = s[y - 1][x + 1];
        if (is_special_char(c)) {
            return make_symbol(c, x + 1, y - 1);
        }
    }

    if (x > 0 && y < s.size() - 1) {
        c = s[y + 1][x - 1];
        if (is_special_char(c)) {
            return make_symbol(c, x - 1, y + 1);
        }
    }

    if (x < s[y].size() - 1 && y < s.size() - 1) {
        c = s[y + 1][x + 1];
        if (is_special_char(c)) {
            return make_symbol(c, x + 1, y + 1);
        }
    }

    return {};
}

std::unordered_map<Symbol, std::vector<int>> build_map(Schema& s) {
    std::unordered_map<Symbol, std::vector<int>> m;
    Number n{};

    for (unsigned y = 0; y < s.size(); y++) {
        for (unsigned x = 0; x < s[y].size(); x++) {
            char c = s[y][x];
            if (std::isdigit(c)) {
                n.str.append(1, c);
                auto sym = get_symbol(s, x, y);
                if (sym) {
                    n.symbol = sym.value();
                }
            } else {
                if (n.symbol.c) {
                    m[n.symbol].push_back(std::stoi(n.str));
                }
                n = {};
            }
        }
    }

    return m;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "no input file" << std::endl;
        return 1;
    }

    std::string file_name = argv[1];
    std::ifstream file_stream;
    
    try {
        file_stream = get_file_stream(file_name);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    }

    Schema s;
    std::string line;
    while (std::getline(file_stream, line)) {
        std::vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        s.push_back(row);
    }

    int result_part_1 = 0;
    int result_part_2 = 0;

    auto schema_map = build_map(s);
    for (const auto& [sym, vec] : schema_map) {
        result_part_1 += std::accumulate(vec.begin(), vec.end(), 0);
        if (sym.c == '*' && vec.size() == 2) {
            result_part_2 += std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
        }
    }

    std::cout << result_part_1 << std::endl;
    std::cout << result_part_2 << std::endl;

    return 0;
}
