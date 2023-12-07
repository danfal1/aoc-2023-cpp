#include "lexer.hpp"
#include "parser.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

std::ifstream get_file_stream(std::string file_name) {
    std::ifstream ifs(file_name);
    if (!ifs) {
        throw std::runtime_error("failed to open input file");
    }
    return ifs;
}

bool is_game_possible(Game g) {
    for (const auto& r : g.rounds) {
        if (MAX_RED - r.cnt_red < 0 || MAX_GREEN - r.cnt_green < 0 || MAX_BLUE - r.cnt_blue < 0) {
            return false;
        }
    }
    return true;
}

int get_cube_power(Game g) {
    int min_red = 0;
    int min_green = 0;
    int min_blue = 0;

    for (const auto& r: g.rounds) {
        if (min_red < r.cnt_red) {
            min_red = r.cnt_red;
        }
        if (min_green < r.cnt_green) {
            min_green = r.cnt_green;
        }
        if (min_blue < r.cnt_blue) {
            min_blue = r.cnt_blue;
        }
    }

    return min_red * min_green * min_blue;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "no input file" << std::endl;
        return -1;
    }

    std::string file_name = argv[1];
    std::ifstream file_stream = get_file_stream(file_name);

    int part_1_result = 0;
    int part_2_result = 0;

    std::string line;
    while (std::getline(file_stream, line)) {
        std::stringstream line_stream(line);
        std::vector<Token> toks = get_tokens(line_stream);
        Game g = make_game(toks);

        if (is_game_possible(g)) {
            part_1_result += g.id;
        }
        part_2_result += get_cube_power(g);
    }

    std::cout << part_1_result << std::endl;
    std::cout << part_2_result << std::endl;

    return 0;
}
