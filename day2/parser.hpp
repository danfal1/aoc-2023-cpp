#pragma once

#include "lexer.hpp"

#include <vector>

enum State_t {
    STATE_S0,
    STATE_S1,
    STATE_S2,
    STATE_S3,
    STATE_S4,
    STATE_S5,
    STATE_S6,
    STATE_S7,
    STATE_ERROR,
};

typedef struct {
    int cnt_red;
    int cnt_green;
    int cnt_blue;
} Round;

typedef struct {
    int id;
    std::vector<Round> rounds;
} Game;

Game make_game(std::vector<Token> toks);
