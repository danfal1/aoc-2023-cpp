#include <cctype>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<char>> Schema;

std::ifstream get_file_stream(std::string file_name) {
    std::ifstream ifs(file_name);
    if (!ifs) {
        throw std::runtime_error("failed to open input file");
    }
    return ifs;
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

    for (auto row : s) {
        for (auto c : row) {
            std::cout << c;
        }
        std::cout << '\n';
    }

    return 0;
}
