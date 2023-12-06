#include "lexer.hpp"

#include <stdexcept>
#include <sstream>

Token make_token(Token_t type, std::optional<std::string> maybe_value) {
    Token t;
    t.type = type;
    if (maybe_value) {
        t.value = maybe_value.value();
    }
    return t;
}

bool is_valid_keyword(std::string& s) {
    if (s == "Game" || s == "red" || s == "green" || s == "blue") {
        return true;
    }
    return false;
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
            if (!is_valid_keyword(s)) {
                throw std::runtime_error("unknown keyword detected");
            }
            toks.push_back(make_token(TOK_KW, s));
        } else {
            throw std::runtime_error("parse error");
        }
    }

    return toks;
}
