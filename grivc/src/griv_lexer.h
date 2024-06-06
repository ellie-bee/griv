#pragma once

#include <stdlib.h>

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_PERIOD,
    TOKEN_SYMBOL,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_UNQUOTE,
    TOKEN_QUASIQUOTE,
    TOKEN_QUOTE,
    TOKEN_UNQUOTE_SPLICE,
    TOKEN_FAILED
} TOKEN_TYPE;

typedef struct {
    TOKEN_TYPE type;
    size_t start;
    int length;
    int line;
    int column;
} TOKEN;

typedef struct {
    TOKEN *tokens;
    size_t count;
    size_t capacity;
} TOK_STREAM;

typedef struct {
    char *input;
    size_t start;
    size_t current;
    int line;
    int column;
} LEXER;

void init_lexer(LEXER *lexer, char *input);
void free_lexer(LEXER *lexer);

TOKEN peek_token(LEXER *lexer);
TOKEN next_token(LEXER *lexer);
TOK_STREAM tokenize(char *input);

void print_tokens(const char *input, TOKEN *tokens);

void token_stream_init(TOK_STREAM *stream);
void token_stream_push(TOK_STREAM *stream, TOKEN token);
void token_stream_free(TOK_STREAM *stream);
void token_stream_print_tokens(TOK_STREAM *stream, const char *input);




