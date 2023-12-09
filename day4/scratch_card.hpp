#pragma once

#include <vector>

class ScratchCard {
    std::vector<int> winning_nums;
    std::vector<int> my_nums;
public:
    int get_win_count() const;
    void set_numbers(std::vector<int> winning, std::vector<int> my);
};

