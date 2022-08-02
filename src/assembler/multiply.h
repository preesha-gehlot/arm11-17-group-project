#ifndef ASSEMBLE_MULTIPLY_H
#define ASSEMBLE_MULTIPLY_H

#include <string.h>

#include "../definitions.h"
#include "tokenizer.h"
#include "utils.h"

#define MUL_COND_VAL AL
#define A_SHIFT_VAL 21
#define MUL_S_SHIFT_VAL 20
#define MUL_RD_SHIFT_VAL 16
#define MUL_RN_SHIFT_VAL 12
#define MUL_RS_SHIFT_VAL 8
#define BITS_4_7_SHIFT_VAL 4
#define BITS_4_7_VAL 9

u_word multiply(instruction_t *instructs);

#endif
