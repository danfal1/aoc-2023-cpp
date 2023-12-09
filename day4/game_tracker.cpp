#include "game_tracker.hpp"
#include <memory>
#include <iostream>

void GameTracker::add_scratch_card(int id, std::shared_ptr<ScratchCard> s) {
    m[id] = s;
}

int GameTracker::get_cnt_total_points() {
    int result = 0;

    for (const auto& [id, s] : m) {
        int win_count = s->get_win_count();
        if (!win_count) {
            continue;
        }

        int partial = 1;
        for (int i = 1; i < win_count; i++) {
            partial *= 2;
        }
        result += partial;
    }

    return result;
}

int GameTracker::get_cnt_copies(int id) {
    int result = 0;

    if (seen.count(id)) {
        return seen.at(id);
    }

    for (int i = 1; i <= m[id]->get_win_count(); i++) {
        result += get_cnt_copies(id + i);
    }

    result++;
    seen[id] = result;
    return result;
}

int GameTracker::get_cnt_total_copies(int id) {
    int result = 0;
    for (const auto& [id, s] : m) {
        result += get_cnt_copies(id);
    }

    return result;
}

int GameTracker::get_first_id() {
    return m.begin()->first;
}
