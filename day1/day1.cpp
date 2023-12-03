#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>

std::string load_file_content(std::string file_name) {
    std::ifstream ifs(file_name);
    std::string content(
        (std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>())
    );
    return content;
}

std::string replace_words(std::string line) {
    std::map<std::string, std::string> m = {
        {"one", "o1e"},
        {"two", "t2o"},
        {"three", "t3e"},
        {"four", "f4r"},
        {"five", "f5e"},
        {"six", "s6x"},
        {"seven", "s7n"},
        {"eight", "e8t"},
        {"nine", "n9e"},
    };

    std::string partial = "";
    for (char c : line) {
        partial.append(1, c);
        for (std::map<std::string, std::string>::iterator it = m.begin(); it != m.end(); it++) {
            if (size_t pos = partial.find(it->first); pos != std::string::npos) {
                partial.replace(pos, pos + it->first.length(), it->second);
            }
        }
    }

    return partial;
}

int get_calibration_digit(std::string line) {
    std::vector<char> digits;
    for (char c : line) {
        if (isdigit(c)) {
            digits.push_back(c);
        }
    }
    std::string final_digit = std::string(1, digits.front()) + std::string(1, digits.back());
    return std::stoi(final_digit);
}

int solve_part_1(std::string file_content) {
    int result = 0;
    std::istringstream stream(file_content);

    for (std::string line; std::getline(stream, line);) {
        result += get_calibration_digit(line);
    }

    return result;
}

int solve_part_2(std::string file_content) {
    int result = 0;
    std::istringstream stream(file_content);

    for (std::string line; std::getline(stream, line);) {
        line = replace_words(line);
        result += get_calibration_digit(line);
    }

    return result;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "no input file" << std::endl;
        return -1;
    }

    std::string file_name = argv[1];
    std::string file_content = load_file_content(file_name);

    int result_part_1 = solve_part_1(file_content);
    int result_part_2 = solve_part_2(file_content);

    std::cout << result_part_1 << std::endl;
    std::cout << result_part_2 << std::endl;

    return 0;
}