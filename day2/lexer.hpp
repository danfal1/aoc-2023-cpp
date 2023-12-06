#pragma once

#include <string>
#include <vector>
#include <optional>

enum Token_t {
    TOK_KW_GAME,
    TOK_KW_RED,
    TOK_KW_GREEN,
    TOK_KW_BLUE,
    TOK_NUM,
    TOK_COL,
    TOK_SEP,
    TOK_EOR,
};

typedef struct {
    Token_t type;
    std::string value;
} Token;

std::vector<Token> get_tokens(std::stringstream& line);
