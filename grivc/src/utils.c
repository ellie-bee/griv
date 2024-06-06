#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void die(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    exit(-1);
}

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file)
        die("Error: Could not open file %s\n", filename);

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (!buffer)
        die("Error: Could not allocate memory\n");

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);

    return buffer;
}