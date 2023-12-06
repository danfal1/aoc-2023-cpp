#include "parser.hpp"
#include "lexer.hpp"

#include <stdexcept>
#include <vector>

#define TERMINAL_STATE STATE_S5

bool is_game_keyword(std::string s) {
    return s == "Game";
}

bool is_color_keyword(std::string s) {
    return s == "red" || s == "green" || s == "blue";
}

State_t transition(State_t current, const Token& tok) {
    switch (current) {
        case STATE_S0:
            switch (tok.type) {
                case TOK_KW:
                    if (!is_game_keyword(tok.value)) {
                        throw std::runtime_error("invalid keyword");
                    }
                    return STATE_S1;
                default:
                    throw std::runtime_error("invalid state");
            }
        case STATE_S1:
            switch (tok.type) {
                case TOK_NUM:
                    return STATE_S2;
                default:
                    throw std::runtime_error("invalid state");
            }
        case STATE_S2:
            switch (tok.type) {
                case TOK_COL:
                    return STATE_S3;
                default:
                    throw std::runtime_error("invalid state");
            }
        case STATE_S3:
            switch (tok.type) {
                case TOK_NUM:
                    return STATE_S4;
                default:
                    throw std::runtime_error("invalid state");
            }
        case STATE_S4:
            switch (tok.type) {
                case TOK_KW:
                    if(!is_color_keyword(tok.value)) {
                        throw std::runtime_error("invalid keyword");
                    }
                    return STATE_S5;
                default:
                    throw std::runtime_error("invalid state");
            }
        case STATE_S5:
            switch (tok.type) {
                case TOK_SEP:
                    return STATE_S6;
                case TOK_EOR:
                    return STATE_S7;
                default:
                    throw std::runtime_error("invalid state");
            }
        case STATE_S6:
            switch (tok.type) {
                case TOK_NUM:
                    return STATE_S4;
                default:
                    throw std::runtime_error("invalid state");
            }
        case STATE_S7:
            switch (tok.type) {
                case TOK_NUM:
                    return STATE_S4;
                default:
                    throw std::runtime_error("invalid state");
            }
        default:
            throw std::runtime_error("unknown state");
    }
}

Game make_game(std::vector<Token> toks) {
    Game g;
    Round r;

    State_t current = STATE_S0;
    for (const auto& tok : toks) {
        current = transition(current, tok);
    }

    if (current != TERMINAL_STATE) {
        throw std::runtime_error("end state was not terminal");
    }

    return g;
}
