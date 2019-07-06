#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer();

void print_prompt();

void read_input(InputBuffer* input_buffer);

void close_input_buffer(InputBuffer* input_buffer);

#endif
