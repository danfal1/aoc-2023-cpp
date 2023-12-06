#include "lexer.hpp"
#include "parser.hpp"

#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

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

    std::string line;
    while (std::getline(file_stream, line)) {
        std::stringstream line_stream(line);
        std::vector<Token> toks = get_tokens(line_stream);
        Game g = make_game(toks);
        std::cout << g.id << std::endl;
        for (auto r : g.rounds) {
            std::cout << "Red: " << r.cnt_red << " ";
            std::cout << "Green: " << r.cnt_green << " ";
            std::cout << "Blue: " << r.cnt_blue << '\n';
        }
        std::cout << "----" << '\n';
    }

    return 0;
}
