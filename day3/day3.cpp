#include <cctype>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<char>> Schema;

typedef struct {
    std::string str;
    bool is_engine_part;
} Number;

std::ifstream get_file_stream(std::string file_name) {
    std::ifstream ifs(file_name);
    if (!ifs) {
        throw std::runtime_error("failed to open input file");
    }
    return ifs;
}

bool is_part_number(Schema& s, unsigned x, unsigned y) {
    bool is_symbol_left = x > 0 && s[y][x - 1] != '.' && std::ispunct(s[y][x - 1]);
    bool is_symbol_right = x < s[y].size() - 1 && s[y][x + 1] != '.' && std::ispunct(s[y][x + 1]);
    bool is_symbol_up = y > 0 && s[y - 1][x] != '.' && std::ispunct(s[y - 1][x]); 
    bool is_symbol_down = y < s.size() - 1 && s[y + 1][x] != '.' && std::ispunct(s[y + 1][x]);
    bool is_symbol_up_left = x > 0 && y > 0 && s[y - 1][x - 1] != '.' && std::ispunct(s[y - 1][x - 1]);
    bool is_symbol_up_right = x < s[y].size() - 1 && y > 0 && s[y - 1][x + 1] != '.' && std::ispunct(s[y - 1][x + 1]);
    bool is_symbol_down_left = x > 0 && y < s.size() - 1 && s[y + 1][x - 1] != '.' && std::ispunct(s[y + 1][x - 1]);
    bool is_symbol_down_right = x < s[y].size() - 1 && y < s.size() - 1 && s[y + 1][x + 1] != '.' && std::ispunct(s[y + 1][x + 1]);

    return is_symbol_left || is_symbol_right || is_symbol_up || is_symbol_down || is_symbol_up_left
        || is_symbol_up_right || is_symbol_down_left || is_symbol_down_right;
}

int sum_engine_parts(Schema& s) {
    Number n{};
    int result = 0;

    for (unsigned y = 0; y < s.size(); y++) {
        for (unsigned x = 0; x < s[y].size(); x++) {
            char c = s[y][x];
            if (std::isdigit(c)) {
                n.str.append(1, c);
                if (!n.is_engine_part) {
                    n.is_engine_part = is_part_number(s, x, y);
                }
            } else {
                if (n.str.empty()) {
                    continue;
                }
                if (n.is_engine_part) {
                    result += std::stoi(n.str);
                }
                n = {};
            }
        }
    }

    return result;
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

    int part_1_result = sum_engine_parts(s);

    std::cout << part_1_result << std::endl;

    return 0;
}
