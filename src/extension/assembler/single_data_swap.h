#ifndef SINGLE_DATA_SWAP_H
#define SINGLE_DATA_SWAP_H

#include "../../definitions.h"
#include "../../assembler/definitions.h"

#define BDT_B_FLAG_SHIFT_VAL 22
#define BDT_RN_SHIFT_VAL     16
#define BDT_RD_SHIFT_VAL     12
#define BDT_RM_SHIFT_VAL     0

#define SWP_BASE_VAL  0x01000090

u_word single_data_swap(instruction_t *instruction);

#endif
