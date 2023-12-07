#pragma once

#include <string>
#include <vector>

typedef enum {
    STATE_S0,
    STATE_S1,
    STATE_S2,
    STATE_S3,
    STATE_S4,
    STATE_S5,
    STATE_S6,
    STATE_S7,
    STATE_S8,
    STATE_S9,
    STATE_S10,
    STATE_S11,
    STATE_S12,
    STATE_ERROR,
} State_t;

typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_ERROR,
} Color_t;

typedef struct {
    int cnt_red;
    int cnt_green;
    int cnt_blue;
} Round;

typedef struct {
    int id;
    std::vector<Round> rounds;
} Game;

Game make_game(std::string line);
