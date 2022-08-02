#ifndef ASSEMBLER_BLOCK_DATA_TRANSFER_DEFINITIONS_H
#define ASSEMBLER_BLOCK_DATA_TRANSFER_DEFINITIONS_H

#include <string.h>

#include "../../assembler/definitions.h"
#include "../../assembler/utils.h"
#include "../../assembler/tokenizer.h"

#define BDT_COND_VAL AL
#define BDT_BITS_27_26 1
#define BDT_BITS_27_26_SHIFT_VAL 27
#define BDT_P_SHIFT_VAL 24
#define BDT_U_SHIFT_VAL 23
#define BDT_S_SHIFT_VAL 22
#define BDT_W_SHIFT_VAL 21
#define BDT_L_SHIFT_VAL 20
#define BDT_RN_SHIFT_VAL 16
#define STACK_POINTER_REGISTER 0xd

void set_l_p_u_flag(u_word *result, bool l_flag, bool p_flag, bool u_flag);
void cons_registers(char *registers, u_word *result);
u_word blockDataTransfer(instruction_t *instruction);
u_word process_pop(instruction_t *instruction);
u_word process_push(instruction_t *instruction);


#endif
