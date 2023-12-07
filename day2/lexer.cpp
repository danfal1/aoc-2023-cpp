#include "lexer.hpp"
#include <cctype>

Token make_token(Token_t type, char value) {
    Token t;
    t.type = type;
    t.value = value;
    return t;
}

Token gettok(char c) {
    switch (c) {
        case ':':
            return make_token(TOK_COLON, c);
        case ',':
            return make_token(TOK_SEP, c);
        case ';':
            return make_token(TOK_EOR, c);
    }

    if (std::isspace(c)) {
        return make_token(TOK_WSPACE, c);
    }

    if (std::isalpha(c)) {
        return make_token(TOK_ALPHA, c);
    }

    if (std::isdigit(c)) {
        return make_token(TOK_DIGIT, c);
    }

    return make_token(TOK_ERROR, c);
}
