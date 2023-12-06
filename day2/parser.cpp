#include "parser.hpp"
#include "lexer.hpp"

#include <stdexcept>
#include <vector>

#define TERMINAL_STATE STATE_S5

State_t transition(State_t current, const Token& tok) {
    switch (current) {
        case STATE_S0:
            switch (tok.type) {
                case TOK_KW_GAME:
                    return STATE_S1;
                default:
                    return STATE_ERROR;
            }
        case STATE_S1:
            switch (tok.type) {
                case TOK_NUM:
                    return STATE_S2;
                default:
                    return STATE_ERROR;
            }
        case STATE_S2:
            switch (tok.type) {
                case TOK_COL:
                    return STATE_S3;
                default:
                    return STATE_ERROR;
            }
        case STATE_S3:
            switch (tok.type) {
                case TOK_NUM:
                    return STATE_S4;
                default:
                    return STATE_ERROR;
            }
        case STATE_S4:
            switch (tok.type) {
                case TOK_KW_RED:
                case TOK_KW_GREEN:
                case TOK_KW_BLUE:
                    return STATE_S5;
                default:
                    return STATE_ERROR;
            }
        case STATE_S5:
            switch (tok.type) {
                case TOK_SEP:
                    return STATE_S6;
                case TOK_EOR:
                    return STATE_S7;
                default:
                    return STATE_ERROR;
            }
        case STATE_S6:
            switch (tok.type) {
                case TOK_NUM:
                    return STATE_S4;
                default:
                    return STATE_ERROR;
            }
        case STATE_S7:
            switch (tok.type) {
                case TOK_NUM:
                    return STATE_S4;
                default:
                    return STATE_ERROR;
            }
        default:
            return STATE_ERROR;
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
