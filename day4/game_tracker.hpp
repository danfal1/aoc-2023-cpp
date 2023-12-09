#pragma once

#include "scratch_card.hpp"

#include <map>
#include <memory>
#include <unordered_map>

class GameTracker {
    std::map<int, std::shared_ptr<ScratchCard>> m;
    std::unordered_map<int, int> seen;
public:
    void add_scratch_card(int id, std::shared_ptr<ScratchCard> s);
    int get_cnt_total_points();
    int get_cnt_total_copies(int id);
private:
    int get_cnt_copies(int id);
};
