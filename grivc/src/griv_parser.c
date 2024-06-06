

#include "griv_parser.h"
#include <stdio.h>

// int parse(vec_string *symbol_table, vec_string *string_table, NODE *root, const char *input) {
// 
//     return 0;
// }
// 
// void print_tree(vec_string *symbol_table, vec_string *string_table, NODE *root) {
//     switch(root->n_type) {
//     case NODE_NIL:
//         printf("()");
//     break;
//     case NODE_BOOL:
//         if(root->n_bool)
//             printf("#t");
//         else
//             printf("#f");
//     break;
//     case NODE_INT:
//         printf("%d", root->n_int);
//     break;
//     case NODE_FLOAT:
//         printf("%f", root->n_float);
//     break;
//     case NODE_STRING:
//         printf("%s", string_table->strings[root->n_string_index]);
//     break;
//     case NODE_SYMBOL:
//         printf("%s", symbol_table->strings[root->n_string_index]);
//     break;
//     case NODE_QUOTE:
//         printf("'(");
//         print_tree(symbol_table, string_table, root->car);
//         printf(")");
//     break;
//     case NODE_QUASIQUOTE:
//         printf("`(");
//         print_tree(symbol_table, string_table, root->car);
//         printf(")");
//     break;
//     case NODE_UNQUOTE:
//         printf(",(");
//         print_tree(symbol_table, string_table, root->car);
//         printf(")");
//     break;
//     case NODE_UNQUOTE_SPLICE:
//         printf(",@(");
//         print_tree(symbol_table, string_table, root->car);
//         printf(")");
//     break;
//     case NODE_CONS:
//         printf("(");
//         print_tree(symbol_table, string_table, root->car);
//         printf(" . ");
//         print_tree(symbol_table, string_table, root->cdr);
//         printf(")");
//     break;
//     }
// }