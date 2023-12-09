#include "scratch_card.hpp"
#include "game_tracker.hpp"

#include <cctype>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

std::ifstream get_file_stream(std::string file_name) {
    std::ifstream ifs(file_name);
    if (!ifs) {
        throw std::runtime_error("failed to open input file");
    }
    return ifs;
}

std::vector<int> load_numbers(std::string s) {
    std::vector<int> numbers;

    std::string n;
    for (char c : s) {
        if (std::isdigit(c)) {
            n.append(1, c);
        } else {
            if (!n.empty()) {
                numbers.push_back(std::stoi(n));
                n.clear();
            }
        }
    }

    if (!n.empty()) {
        numbers.push_back(std::stoi(n));
    }

    return numbers;
}

std::shared_ptr<GameTracker> make_game_tracker(std::ifstream& file_stream) {
    auto gt = std::make_shared<GameTracker>(GameTracker());

    std::string line;
    while(std::getline(file_stream, line)) {
        int colon_pos = line.find(':');
        int sep_pos = line.find('|');

        std::string id_str;
        for (char c : line.substr(0, colon_pos)) {
            if (std::isdigit(c)) {
                id_str.append(1, c);
            }
        }

        int id = std::stoi(id_str);
        auto winning_nums = load_numbers(line.substr(colon_pos + 1, sep_pos - colon_pos - 1));
        auto my_nums = load_numbers(line.substr(sep_pos + 1, line.length() - sep_pos - 1));

        auto s = std::make_shared<ScratchCard>(ScratchCard(winning_nums, my_nums));
        gt->add_scratch_card(id, s);
    }

    return gt;
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
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    }

    auto gt = make_game_tracker(file_stream);
    int part_1_result = gt->get_cnt_total_points();
    int part_2_result = gt->get_cnt_total_copies(gt->get_first_id());

    std::cout << part_1_result << std::endl;
    std::cout << part_2_result << std::endl;

    return 0;
}
