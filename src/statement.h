#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "table.h"

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABEL_FULL
} ExecutedResult;

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;


typedef struct {
    StatementType type;
    Row row_to_insert; // only used by insert statement
} Statement;

MetaCommandResult do_meta_command(InputBuffer * input_buffer, Table* table);

PrepareResult prepare_statement(InputBuffer* input_buffer,
                                Statement* statement);

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement);

ExecutedResult execute_statement(Statement* statement, Table* table);

void print_row(Row* row);

#endif
