#include "scratch_card.hpp"

#include <vector>
#include <algorithm>

ScratchCard::ScratchCard(std::vector<int> winning, std::vector<int> my) {
    winning_nums = winning;
    my_nums = my;
}

int ScratchCard::get_win_count() const {
    int result = 0;
    for (int v : my_nums) {
        if (std::find(winning_nums.begin(), winning_nums.end(), v) != winning_nums.end()) {
            result++;
        }
    }

    return result;
}
