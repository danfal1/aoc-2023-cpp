#pragma once

#include <string>
#include <vector>
#include <optional>

enum Token_t {
    TOK_KW,
    TOK_NUM,
    TOK_COL,
    TOK_SEP,
    TOK_EOR,
};

typedef struct {
    Token_t type;
    std::string value;
} Token;

Token make_token(Token_t type, std::optional<std::string> maybe_value);

std::vector<Token> get_tokens(std::stringstream& line);

bool is_valid_keyword(std::string& s);
