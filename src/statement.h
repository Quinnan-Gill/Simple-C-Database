#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include "input.h"

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct {
    unint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

typedef struct {
    StatementType type;
    Row row_to_insert; // only used by insert statement
} Statement;

MetaCommandResult do_meta_command(InputBuffer * input_buffer);

PrepareResult prepare_statement(InputBuffer* input_buffer,
                                Statement* statement);

void execute_statement(Statement* statement);



#endif
