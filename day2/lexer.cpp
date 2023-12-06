#include "lexer.hpp"

#include <stdexcept>
#include <sstream>
#include <optional>

Token make_token(Token_t type, std::optional<std::string> maybe_value) {
    Token t;
    t.type = type;
    if (maybe_value) {
        t.value = maybe_value.value();
    }
    return t;
}

Token_t get_kw_token(std::string& s) {
    if (s == "Game") {
        return TOK_KW_GAME;
    } else if (s == "red") {
        return TOK_KW_RED;
    } else if (s == "green") {
        return TOK_KW_GREEN;
    } else if (s == "blue") {
        return TOK_KW_BLUE;
    } else {
        throw std::runtime_error("invalid token");
    }
}

std::vector<Token> get_tokens(std::stringstream& line) {
    std::vector<Token> toks;
    char c;

    while(line.get(c)) {
        if (std::isspace(c)) {
            continue;
        } else if (c == ':') {
            toks.push_back(make_token(TOK_COL, {}));
        } else if (c == ';') {
            toks.push_back(make_token(TOK_EOR, {}));
        } else if (c == ',') {
            toks.push_back(make_token(TOK_SEP, {}));
        } else if (std::isdigit(c)) {
            std::string s;
            while (std::isdigit(c) && !line.eof()) {
                s.append(1, c);
                line.get(c);
            }
            line.putback(c);
            toks.push_back(make_token(TOK_NUM, s));
        } else if (std::isalpha(c)) {
            std::string s;
            while (std::isalpha(c) && !line.eof()) {
                s.append(1, c);
                line.get(c);
            }
            line.putback(c);
            Token_t kw_token = get_kw_token(s);
            toks.push_back(make_token(kw_token, s));
        } else {
            throw std::runtime_error("parse error");
        }
    }

    return toks;
}
