#ifndef ASSEMBLE_SDT_H
#define ASSEMBLE_SDT_H

#include <string.h>

#include "definitions.h"
#include "utils.h"
#include "data_processing.h"
#include "tokenizer.h"

#define IS_EXPRESSION()   (instruction->ops[1][0] == '=' && instruction->opcode == LDR)
#define IS_PRE_INDEXING() (instruction -> no_of_ops == 2)

#define SDT_COND_VAL AL
#define SDT_BITS_27_26 1
#define SDT_BITS_27_26_SHIFT_VAL 26
#define SDT_I_SHIFT_VAL 25
#define SDT_P_SHIFT_VAL 24
#define SDT_U_SHIFT_VAL 23
#define SDT_L_SHIFT_VAL 20
#define SDT_RN_SHIFT_VAL 16
#define SDT_RD_SHIFT_VAL 12

u_word single_data_transfer(assembler *assembler);
u_address numeric_constant_load(u_word expression, assembler *assembler);
u_word convert_to_mov(instruction_t *instruction);

#endif
