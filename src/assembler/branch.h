#ifndef ASSEMBLE_BRANCH_H
#define ASSEMBLE_BRANCH_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../definitions.h"
#include "../utils.h"
#include "utils.h"
#include "symbol_table.h"
#include "tokenizer.h"

#define BEQ_BITS  0
#define BNE_BITS  1
#define BGE_BITS  10
#define BLT_BITS  11
#define BGT_BITS  12
#define BLE_BITS  13
#define B_BITS    14

#define BRANCH_BASE_BITS      0xA
#define BRANCH_BASE_SHIFT_VAL 24

u_word branch(assembler *ass);

#endif
