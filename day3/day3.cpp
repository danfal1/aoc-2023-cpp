#include <cctype>
#include <cstddef>
#include <fstream>
#include <functional>
#include <numeric>
#include <optional>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

typedef std::vector<std::vector<char>> Schema;

struct Symbol {
    unsigned x;
    unsigned y;
    char c;

    bool operator==(const Symbol& other) const {
        return x == other.x && y == other.y && c == other.c;
    }
};

template <>
struct std::hash<Symbol> {
    std::size_t operator()(const Symbol& s) const {
        using std::size_t;
        using std::hash;
        using std::string;

        // Compute individual hash values for first,
        // second and third and combine them using XOR
        // and bit shifting:

        return ((hash<unsigned>()(s.x)
                 ^ (hash<unsigned>()(s.y) << 1)) >> 1)
                 ^ (hash<char>()(s.c) << 1);
        }
};

typedef struct {
    std::string str;
    Symbol symbol;
} Number;

std::ifstream get_file_stream(std::string file_name) {
    std::ifstream ifs(file_name);
    if (!ifs) {
        throw std::runtime_error("failed to open input file");
    }
    return ifs;
}

bool is_symbol(char c) {
    return c != '.' && std::ispunct(c);
}

Symbol make_symbol(char c, unsigned x, unsigned y) {
    return Symbol{x, y, c};
}

std::optional<Symbol> get_symbol(Schema& s, unsigned x, unsigned y) {
    char c;
    if (x > 0) {
        c = s[y][x - 1];
        if (is_symbol(c)) {
            return make_symbol(c, x - 1, y);
        }
    }

    if (x < s[y].size() - 1) {
        c = s[y][x + 1];
        if (is_symbol(c)) {
            return make_symbol(c, x + 1, y);
        }
    }

    if (y > 0) {
        c = s[y - 1][x];
        if (is_symbol(c)) {
            return make_symbol(c, x, y - 1);
        }
    } 

    if (y < s.size() - 1) {
        c = s[y + 1][x];
        if (is_symbol(c)) {
            return make_symbol(c, x, y + 1);
        }
    }

    if (x > 0 && y > 0) {
        c = s[y - 1][x - 1];
        if (is_symbol(c)) {
            return make_symbol(c, x - 1, y - 1);
        }
    }

    if (x < s[y].size() - 1 && y > 0) {
        c = s[y - 1][x + 1];
        if (is_symbol(c)) {
            return make_symbol(c, x + 1, y - 1);
        }
    }

    if (x > 0 && y < s.size() - 1) {
        c = s[y + 1][x - 1];
        if (is_symbol(c)) {
            return make_symbol(c, x - 1, y + 1);
        }
    }

    if (x < s[y].size() - 1 && y < s.size() - 1) {
        c = s[y + 1][x + 1];
        if (is_symbol(c)) {
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
                    if (auto search = m.find(n.symbol); search != m.end()) {
                        m[n.symbol].push_back(std::stoi(n.str));
                    } else {
                        m[n.symbol] = {std::stoi(n.str)};
                    }
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
        return -1;
    }

    std::string file_name = argv[1];
    std::ifstream file_stream = get_file_stream(file_name);

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
    // for (auto it = schema_map.begin(); it != schema_map.end(); it++) {
    //     std::cout << "Symbol: " << it->first.c << ": ";
    //     for (auto v : it->second) {
    //         std::cout << v << " ";
    //     }
    //     std::cout << '\n';
    // }

    for (auto it = schema_map.begin(); it != schema_map.end(); it++) {
        result_part_1 += std::accumulate(it->second.begin(), it->second.end(), 0);
        if (it->first.c == '*') {
            result_part_2 += std::accumulate(it->second.begin(), it->second.end(), 1, std::multiplies<int>());
        }
    }

    std::cout << result_part_1 << std::endl;
    std::cout << result_part_2 << std::endl;

    return 0;
}
