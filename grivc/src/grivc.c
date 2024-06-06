#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "griv.h"
#include "utils.h"

#include "griv_lexer.h"

typedef struct {
    char *input_file;
    char *output_file;
    int graph;
    int version;
} ARGS;

void print_usage();
int parse_args(ARGS *args, int argc, char **argv);
char *read_file(const char *filename);

int main(int argc, char **argv) {

    ARGS args = {0};
    parse_args(&args, argc, argv);

    char *input = read_file(args.input_file);

    printf("Input: %s\n", input);

    // try to tokenize the input
    TOK_STREAM ts = tokenize(input);

    // print the tokens
    token_stream_print_tokens(&ts, input);

    return 0;
}

void print_usage() {
    printf("Usage: grivc [options] <input file>\n");
    printf("Options:\n");
    printf("  -g/--graph                 produce a human readable graph\n");
    printf("  -o/--output <output file>  Specify output file\n");
    printf("                             If not specified, output will be written to stdout\n");
    printf("  -h/--help                  Print this help message\n");
    printf("  -v/--version               Print version information\n");
}

int parse_args(ARGS *args, int argc, char **argv) {
    if(argc < 2) {
        print_usage();
        exit(-1);
    }

    // parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            print_usage();
            exit(0);
        }

        if (strcmp(argv[i], "-v") == 0) {
            printf("grivc version "GRIVC_VERSION"\n");
            exit(0);
        }

        if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--graph") == 0) {
            args->graph = 1;
            continue;
        }

        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                args->output_file = argv[i + 1];
                i++;
            } else {
                die("Error: -o requires an argument\n");
            }
            continue;
        }

        if (argv[i][0] == '-') {
            die("Error: Unknown option %s\n", argv[i]);
        }

        args->input_file = argv[i];
    }

    return 0;
}
