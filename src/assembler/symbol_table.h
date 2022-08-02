#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>
#include <stdlib.h>

#include "../definitions.h"
#include "../utils.h"

typedef struct {
    char *label;
    u_address address;
    struct stElem *left;
    struct stElem *right;
} stElem;

typedef struct {
    stElem *root;
} symbolTable;

symbolTable *create_table(void);
u_address st_lookup(symbolTable *handle, char *label);
void st_insert(symbolTable *handle, const char *label, u_address address);
void st_free(symbolTable *table);

#endif
