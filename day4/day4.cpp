#include <algorithm>
#include <cctype>
#include <exception>
#include <fstream>
#include <iostream>
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

std::vector<int> load_numbers(std::string& line) {
    std::vector<int> numbers;

    std::string n;
    for (char c : line) {
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

    int part_1_result = 0;

    std::string line;
    while(std::getline(file_stream, line)) {
        std::string n;
        int colon_pos = line.find(':');
        int sep_pos = line.find('|');

        std::string winning = line.substr(colon_pos + 1, sep_pos - colon_pos - 1);
        std::vector<int> winning_numbers = load_numbers(winning);

        std::string my = line.substr(sep_pos + 1, line.length() - sep_pos);
        std::vector<int> my_numbers = load_numbers(my);

        std::vector<int> isect;
        for (int v : my_numbers) {
            if (std::find(winning_numbers.begin(), winning_numbers.end(), v) != winning_numbers.end()) {
                isect.push_back(v);
            }
        }

        if (isect.empty()) {
            continue;
        }

        int points = 1;
        for (unsigned i = 1; i < isect.size(); i++) {
            points *= 2;
        }
        part_1_result += points;
    }

    std::cout << part_1_result << std::endl;

    return 0;
}
