#pragma once

#include <vector>

class ScratchCard {
    std::vector<int> winning_nums;
    std::vector<int> my_nums;
public:
    ScratchCard(std::vector<int> winning, std::vector<int> my);
    int get_win_count() const;
};

