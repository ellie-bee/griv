
#include "griv_lexer.h"
#include <stdio.h>
#include <stdlib.h>

void init_lexer(LEXER *lexer, char *input) {
  lexer->input = input;
  lexer->start = 0;
  lexer->current = 0;
  lexer->line = 1;
  lexer->column = 1;
}

void free_lexer(LEXER *lexer) { free(lexer->input); }

int is_whitespace(char c) {
  return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

int is_digit(char c) { return c >= '0' && c <= '9'; }

TOKEN next_token(LEXER *lexer) {
  TOKEN token = {0};
  token.start = lexer->current;
  token.line = lexer->line;
  token.column = lexer->column;

  char c = lexer->input[lexer->current];

  // skip whitespace
  while (is_whitespace(c)) {
    lexer->column++;
    if (c == '\n') {
      lexer->line++;
      lexer->column = 1;
    }
    c = lexer->input[++lexer->current];
  }

  // skip comments
  if (c == ';') {
    while (c != '\n') {
      c = lexer->input[++lexer->current];
    }
    lexer->line++;
    lexer->column = 1;
    c = lexer->input[++lexer->current];
  }
  token.start = lexer->current;
  token.line = lexer->line;
  token.column = lexer->column;

  // check eof
  if (c == '\0') {
    token.type = TOKEN_EOF;
    return token;
  }

  // check for numbers
  if (is_digit(c) || (c == '-' && is_digit(lexer->input[lexer->current + 1]))) {
    c = lexer->input[++lexer->current];
    token.type = TOKEN_NUMBER;
    while (is_digit(c)) {
      c = lexer->input[++lexer->current];
    }

    if (c == '.') {
      c = lexer->input[++lexer->current];
      while (is_digit(c)) {
        c = lexer->input[++lexer->current];
      }
    }

    token.length = lexer->current - token.start;
    lexer->column += token.length;
    return token;
  }

  // check for strings
  if (c == '"') {
    token.type = TOKEN_STRING;
    c = lexer->input[++lexer->current];
    while (c != '"') {
      if (c == '\n') {
        lexer->line++;
        lexer->column = 1;
      } else {
        lexer->column++;
      }
      c = lexer->input[++lexer->current];
    }
    lexer->current++;
    token.length = lexer->current - token.start;
    lexer->column += token.length;
    return token;
  }

  if (c == '(') {
    token.type = TOKEN_OPEN_PAREN;
    lexer->current++;
    lexer->column++;
    token.length = 1;
    return token;
  }

  if (c == ')') {
    token.type = TOKEN_CLOSE_PAREN;
    lexer->current++;
    lexer->column++;
    token.length = 1;
    return token;
  }

  if (c == ',') {
    if (lexer->input[lexer->current + 1] == '@') {
      token.type = TOKEN_UNQUOTE_SPLICE;
      token.length = 2;
      lexer->current += 2;
      lexer->column += 2;
    } else {
      token.type = TOKEN_UNQUOTE;
      token.length = 1;
      lexer->current++;
      lexer->column++;
    }

    return token;
  }

  if (c == '.') {
    token.type = TOKEN_PERIOD;
    lexer->current++;
    lexer->column++;
    token.length = 1;
    return token;
  }

  if (c == '`') {
    token.type = TOKEN_QUASIQUOTE;
    lexer->current++;
    lexer->column++;
    token.length = 1;
    return token;
  }

  if (c == '\'') {
    token.type = TOKEN_QUOTE;
    lexer->current++;
    lexer->column++;
    token.length = 1;
    return token;
  }

  token.type = TOKEN_SYMBOL;
  while (!is_whitespace(c) && c != '(' && c != ')' && c != '\0' && c != ';' &&
         c != '"' && c != '\'' && c != '`' && c != ',') {
    c = lexer->input[++lexer->current];
    lexer->column++;
  }

  token.length = lexer->current - token.start;

  return token;
}

TOK_STREAM tokenize(char *input) {
  TOK_STREAM stream = {0};
  token_stream_init(&stream);

  LEXER lexer = {0};
  init_lexer(&lexer, input);

  TOKEN token = {0};
  do {
    token = next_token(&lexer);
    token_stream_push(&stream, token);
  } while (token.type != TOKEN_EOF);

  return stream;
}

const char *tok_to_str(TOKEN *t) {
  switch (t->type) {
  case TOKEN_EOF:
    return "EOF           ";
  case TOKEN_NUMBER:
    return "NUMBER        ";
  case TOKEN_STRING:
    return "STRING        ";
  case TOKEN_SYMBOL:
    return "SYMBOL        ";
  case TOKEN_OPEN_PAREN:
    return "OPEN_PAREN    ";
  case TOKEN_CLOSE_PAREN:
    return "CLOSE_PAREN   ";
  case TOKEN_UNQUOTE:
    return "UNQUOTE       ";
  case TOKEN_QUASIQUOTE:
    return "QUASIQUOTE    ";
  case TOKEN_QUOTE:
    return "QUOTE         ";
  case TOKEN_UNQUOTE_SPLICE:
    return "UNQUOTE_SPLICE";
  case TOKEN_PERIOD:
    return "PERIOD        ";
  default:
    return "UNKNOWN       ";
  }
}

void token_stream_init(TOK_STREAM *stream) {
  stream->tokens = malloc(sizeof(TOKEN) * 1024);
  stream->count = 0;
  stream->capacity = 1024;
}

void token_stream_push(TOK_STREAM *stream, TOKEN token) {
  if (stream->count == stream->capacity) {
    stream->capacity *= 2;
    stream->tokens = realloc(stream->tokens, sizeof(TOKEN) * stream->capacity);
  }

  stream->tokens[stream->count++] = token;
}

void token_stream_free(TOK_STREAM *stream) { free(stream->tokens); }

void token_stream_print_tokens(TOK_STREAM *stream, const char *input) {
  for (size_t i = 0; i < stream->count; i++) {
    TOKEN *t = &stream->tokens[i];
    // print the token type, length, and line number
    printf("%s (%d, %d), start: %zu, length: %d, ", tok_to_str(t), t->line,
           t->column, t->start, t->length);
    printf("value: %.*s\n", t->length, input + t->start);
  }
}