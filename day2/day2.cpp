#include <cctype>
#include <fstream>
#include <iostream>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

enum Token_t {
    TOK_KW,
    TOK_NUM,
    TOK_COL,
    TOK_SEP,
    TOK_EOR,
};

typedef struct {
    Token_t type;
    std::optional<std::string> maybe_value;
} Token;

Token make_token(Token_t type, std::optional<std::string> maybe_value) {
    Token t;
    t.type = type;
    t.maybe_value = maybe_value;
    return t;
}

std::ifstream get_file_stream(std::string file_name) {
    std::ifstream ifs(file_name);
    if (!ifs) {
        throw std::runtime_error("failed to open input file");
    }
    return ifs;
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

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "no input file" << std::endl;
        return -1;
    }

    std::string file_name = argv[1];
    std::ifstream file_stream = get_file_stream(file_name);

    std::string line;
    while (std::getline(file_stream, line)) {
        std::stringstream line_stream(line);
        std::vector<Token> toks = get_tokens(line_stream);
        for (const auto& t : toks) {
            std::cout << "[Token: " << t.type << "]: " << t.maybe_value.value_or("NONE") << '\n';
            std::cout << "----" << '\n';
        }
    }

    return 0;
}
