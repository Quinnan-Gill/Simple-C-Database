#ifndef _ROW_H_
#define _ROW_H_

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "queue.h"

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

static const uint32_t ID_SIZE = size_of_attribute(Row, id);
static const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
static const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
static const uint32_t ID_OFFSET = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

void serialize_row(Row* source, void* destination);

void deserialize_row(void* source, Row* destination);

static const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100

typedef struct {
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void *pages[TABLE_MAX_PAGES];
} Pager;

typedef struct {
    Pager* pager;
    uint32_t root_page_num;
} Table;

Table* new_table();

void* get_page(Pager* pager, uint32_t page_num);

Table* db_open(const char* filename);

Pager* pager_open(const char* filename);

void pager_flush(Pager* pager, uint32_t page_num);

uint32_t get_unused_page_num(Pager* pager);

void db_close(Table* table);

// ------------------------------------------------
//                     Cursor
// ------------------------------------------------

typedef struct {
    Table* table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table; // Indicates a position one past the last element
} Cursor;

Cursor* table_start(Table* table);

Cursor* table_find(Table* table, uint32_t key);

void* cursor_value(Cursor* cursor);

void cursor_advance(Cursor* cursor);

// ------------------------------------------------
//                     Node
// ------------------------------------------------

typedef enum {
    NODE_INTERNAL,
    NODE_LEAF
} NodeType;

/*
 * Common Node Header Layout
 */
static const uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
static const uint32_t NODE_TYPE_OFFSET = 0;
static const uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
static const uint32_t IS_ROOT_OFFSET = NODE_TYPE_SIZE;
static const uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
static const uint32_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE;
static const uint32_t COMMON_NODE_HEADER_SIZE =
    NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;

/*
 * Leaf Node Header Layout
 */
static const uint32_t LEAF_NODE_NUM_CELLS_SIZE = sizeof(uint32_t);
static const uint32_t LEAF_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
static const uint32_t LEAF_NODE_NEXT_LEAF_SIZE = sizeof(uint32_t);
static const uint32_t LEAF_NODE_NEXT_LEAF_OFFSET =
    LEAF_NODE_NUM_CELLS_OFFSET + LEAF_NODE_NUM_CELLS_SIZE;
static const uint32_t LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE +
                                              LEAF_NODE_NUM_CELLS_SIZE +
                                              LEAF_NODE_NEXT_LEAF_SIZE;

/*
 * Leaf Node Body Layout
 */
static const uint32_t LEAF_NODE_KEY_SIZE = sizeof(uint32_t);
static const uint32_t LEAF_NODE_KEY_OFFSET = 0;
static const uint32_t LEAF_NODE_VALUE_SIZE = ROW_SIZE;
static const uint32_t LEAF_NODE_VALUE_OFFSET =
    LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE;
static const uint32_t LEAF_NODE_CELL_SIZE = LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE;
static const uint32_t LEAF_NODE_SPACE_FOR_CELLS =  PAGE_SIZE - LEAF_NODE_HEADER_SIZE;
#ifdef DEBUG
static const uint32_t LEAF_NODE_MAX_CELLS = 3;
#else
static const uint32_t LEAF_NODE_MAX_CELLS =
    LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE;
#endif

static const uint32_t LEAF_NODE_RIGHT_SPLIT_COUNT = (LEAF_NODE_MAX_CELLS + 1) / 2;
static const uint32_t LEAF_NODE_LEFT_SPLIT_COUNT =
    (LEAF_NODE_MAX_CELLS + 1) - LEAF_NODE_RIGHT_SPLIT_COUNT;

/*
 * Internal Node Header Layout
 */
static const uint32_t INTERNAL_NODE_NUM_KEYS_SIZE = sizeof(uint32_t);
static const uint32_t INTERNAL_NODE_NUM_KEYS_OFFSET = COMMON_NODE_HEADER_SIZE;
static const uint32_t INTERNAL_NODE_RIGHT_CHILD_SIZE = sizeof(uint32_t);
static const uint32_t INTERNAL_NODE_RIGHT_CHILD_OFFSET =
    INTERNAL_NODE_NUM_KEYS_OFFSET + INTERNAL_NODE_NUM_KEYS_SIZE;
static const uint32_t INTERNAL_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE +
                                           INTERNAL_NODE_NUM_KEYS_SIZE +
                                           INTERNAL_NODE_RIGHT_CHILD_SIZE;

/*
 * Internal Node Body Layout
 */
static const uint32_t INTERNAL_NODE_KEY_SIZE = sizeof(uint32_t);
static const uint32_t INTERNAL_NODE_CHILD_SIZE = sizeof(uint32_t);
static const uint32_t INTERNAL_NODE_CELL_SIZE =
    INTERNAL_NODE_CHILD_SIZE + INTERNAL_NODE_KEY_SIZE;
/* Keep this small for testing */
static const uint32_t INTERNAL_NODE_MAX_CELLS = 3;

static const uint32_t INTERNAL_NODE_RIGHT_SPLIT_COUNT = (INTERNAL_NODE_MAX_CELLS + 1) / 2;
static const uint32_t INTERNAL_NODE_LEFT_SPLIT_COUNT =
  (INTERNAL_NODE_MAX_CELLS + 1) - INTERNAL_NODE_RIGHT_SPLIT_COUNT;

/*
 * Root Nodes
 */
void create_new_root(Table* table, uint32_t right_child_page_num);

void reset_parents_after_root(Table* table, uint32_t parent_page_num);

bool is_node_root(void* node);

/*
 * Leaf Nodes
 */
uint32_t* leaf_node_num_cells(void* node);

void* leaf_node_cell(void* node, uint32_t cell_num);

uint32_t* leaf_node_key(void* node, uint32_t cell_num);

void* leaf_node_value(void* node, uint32_t cell_num);

void initialize_leaf_node(void* node);

void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value);

Cursor* leaf_node_find(Table* table, uint32_t page_num, uint32_t key);

void leaf_node_split_and_insert(Cursor* cursor, uint32_t key, Row* value);

uint32_t* leaf_node_next_leaf(void* node);

/*
 * Internal Nodes
 */

uint32_t* internal_node_num_keys(void* node);

uint32_t* internal_node_right_child(void* node);

uint32_t* internal_node_cell(void* node, uint32_t cell_num);

uint32_t* internal_node_child(void* node, uint32_t child_num);

uint32_t* internal_node_key(void* node, uint32_t key_num);

uint32_t get_node_max_key(void* node);

uint32_t get_node_max_descendant(Table* table, void* node);

void set_node_root(void* node, bool is_root);

void initialize_interal_node(void* node);

uint32_t internal_node_find_child(void* node, uint32_t key);

Cursor* internal_node_find(Table* table, uint32_t page_num, uint32_t key);

void update_internal_node_key(void* node, uint32_t old_key, uint32_t new_key);

void internal_node_insert(Table* table, uint32_t parent_page_num,
                          uint32_t child_page_num);

void internal_node_split_and_insert(Table* table, uint32_t parent_page_num);

void internal_remove_max_key(void* node);

/*
 * General Node Info
 */

NodeType get_node_type(void* node);

void set_node_type(void* node, NodeType type);

uint32_t* node_parent(void* node);

void print_constants();

void indent(uint32_t level);

void print_tree(Pager* pager, uint32_t page_num, uint32_t indentation_level);

void pretty_print_tree(Pager* pager, uint32_t page_num);

#endif
