#pragma once

#include <stdlib.h>

typedef enum {
    NODE_NIL = 0,
    NODE_CONS,
    NODE_BOOL,
    NODE_INT,
    NODE_FLOAT,
    NODE_STRING,
    NODE_SYMBOL,
    NODE_QUOTE,
    NODE_QUASIQUOTE,
    NODE_UNQUOTE,
    NODE_UNQUOTE_SPLICE
} NODE_TYPE;

typedef struct NODE {
    NODE_TYPE n_type;
    union {
        int n_int;
        int n_bool;
        float n_float;
        size_t n_symbol_index;
        size_t n_string_index;
        struct {
            struct NODE *car;
            struct NODE *cdr;
        };
    };
} NODE;

typedef struct {
    size_t capacity;
    size_t count;
    char **strings;
} vec_string;

int parse(vec_string *symbol_table, vec_string *string_table, NODE *root, const char *input);

void print_tree(vec_string *symbol_table, vec_string *string_table, NODE *root);
