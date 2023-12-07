#pragma once

typedef enum {
    TOK_ALPHA,
    TOK_DIGIT,
    TOK_WSPACE,
    TOK_COLON,
    TOK_SEP,
    TOK_EOR,
    TOK_ERROR,
} Token_t;

typedef struct{
    Token_t type;
    char value;
} Token;

Token gettok(char c);
