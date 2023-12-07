#include "parser.hpp"
#include "lexer.hpp"

#include <stdexcept>
#include <string>

#define TERMINAL_STATE STATE_S10

State_t transition(State_t current, Token t) {
    switch (current) {
        case STATE_S0:
            switch (t.type) {
                case TOK_ALPHA:
                    return STATE_S1;
                default:
                    return STATE_ERROR;
            }
        case STATE_S1:
            switch (t.type) {
                case TOK_ALPHA:
                    return STATE_S1;
                case TOK_WSPACE:
                    return STATE_S2;
                default:
                    return STATE_ERROR;
            }
        case STATE_S2:
            switch (t.type) {
                case TOK_WSPACE:
                    return STATE_S3;
                case TOK_DIGIT:
                    return STATE_S4;
                default:
                    return STATE_ERROR;
            }
        case STATE_S3:
            switch (t.type) {
                case TOK_WSPACE:
                    return STATE_S3;
                case TOK_DIGIT:
                    return STATE_S4;
                default:
                    return STATE_ERROR;
            }
        case STATE_S4:
            switch (t.type) {
                case TOK_DIGIT:
                    return STATE_S4;
                case TOK_COLON:
                    return STATE_S5;
                default:
                    return STATE_ERROR;
            }
        case STATE_S5:
            switch (t.type) {
                case TOK_WSPACE:
                    return STATE_S6;
                case TOK_DIGIT:
                    return STATE_S7;
                default:
                    return STATE_ERROR;
            }
        case STATE_S6:
            switch (t.type) {
                case TOK_WSPACE:
                    return STATE_S6;
                case TOK_DIGIT:
                    return STATE_S7;
                default:
                    return STATE_ERROR;
            }
        case STATE_S7:
            switch (t.type) {
                case TOK_DIGIT:
                    return STATE_S7;
                case TOK_WSPACE:
                    return STATE_S8;
                default:
                    return STATE_ERROR;
            }
        case STATE_S8:
            switch (t.type) {
                case TOK_ALPHA:
                    return STATE_S10;
                case TOK_WSPACE:
                    return STATE_S9;
                default:
                    return STATE_ERROR;
            }
        case STATE_S9:
            switch (t.type) {
                case TOK_WSPACE:
                    return STATE_S9;
                case TOK_ALPHA:
                    return STATE_S10;
                default:
                    return STATE_ERROR;
            }
        case STATE_S10:
            switch (t.type) {
                case TOK_ALPHA:
                    return STATE_S10;
                case TOK_SEP:
                    return STATE_S11;
                case TOK_EOR:
                    return STATE_S12;
                default:
                    return STATE_ERROR;
            }
        case STATE_S11:
            switch (t.type) {
                case TOK_WSPACE:
                    return STATE_S6;
                case TOK_DIGIT:
                    return STATE_S7;
                default:
                    return STATE_ERROR;
            }
        case STATE_S12:
            switch (t.type) {
                case TOK_WSPACE:
                    return STATE_S6;
                case TOK_DIGIT:
                    return STATE_S7;
                default:
                    return STATE_ERROR;
            }
        default:
            return STATE_ERROR;
    }
}

Color_t get_color(std::string s) {
    if (s == "red") {
        return COLOR_RED;
    } else if (s == "green") {
        return COLOR_GREEN;
    } else if (s == "blue") {
        return COLOR_BLUE;
    } else {
        return COLOR_ERROR;
    }
}

bool set_color(Round& r, Color_t color, int amount) {
    switch (color) {
        case COLOR_RED:
            r.cnt_red = amount;
            break;
        case COLOR_GREEN:
            r.cnt_green = amount;
            break;
        case COLOR_BLUE:
            r.cnt_blue = amount;
            break;
        default:
            return false;
    }

    return true;
}

Game make_game(std::string line) {
    Game g;
    std::vector<Round> rounds{{}};

    std::string current_string;
    Color_t current_color;
    int current_count;

    int round_index = 0;
    State_t current = STATE_S0;
    for (auto c : line) {
        Token tok = gettok(c);
        current = transition(current, tok);
        switch (current) {
            case STATE_S1:
            case STATE_S4:
            case STATE_S7:
            case STATE_S10:
                current_string.append(1, c);
                break;
            case STATE_S2:
                if (current_string != "Game") {
                    throw std::runtime_error("expected keyword Game");
                }
                current_string.clear();
                break;
            case STATE_S5:
                g.id = std::stoi(current_string);
                current_string.clear();
                break;
            case STATE_S8:
                current_count = std::stoi(current_string);
                current_string.clear();
                break;
            case STATE_S12:
                current_color = get_color(current_string);
                if (!set_color(rounds[round_index], current_color, current_count)) {
                    throw std::runtime_error("failed to set color");
                }
                current_string.clear();
                rounds.push_back({});
                round_index++;
                break;
            case STATE_S11:
                current_color = get_color(current_string);
                if (!set_color(rounds[round_index], current_color, current_count)) {
                    throw std::runtime_error("failed to set color");
                }
                current_string.clear();
                break;
            case STATE_ERROR:
                throw std::runtime_error("malformed input");
            default:
                break;
        }
    }

    if (current != TERMINAL_STATE) {
        throw std::runtime_error("malformed input");
    }

    current_color = get_color(current_string);
    if (!set_color(rounds[round_index], current_color, current_count)) {
        throw std::runtime_error("failed to set color");
    }
    current_string.clear();

    g.rounds = rounds;
    return g;
}
