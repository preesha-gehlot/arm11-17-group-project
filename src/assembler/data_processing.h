#ifndef ASSEMBLE_DATAPROCESSING_H
#define ASSEMBLE_DATAPROCESSING_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../utils.h"
#include "../definitions.h"
#include "definitions.h"
#include "utils.h"

#define SHIFT_DELIMITER " "
#define MAX_SHIFTS      16

#define IMMEDIATE_SHIFT_VAL       8
#define OP2_IMMEDIATE_SHIFT_VAL   7
#define RS_SHIFT_VAL              8
#define SHIFT_BY_REG_FLAG_BITS  0x10
#define I_FLAG_VAL              0x2000000
#define DPC_COND_VAL              AL
#define OPCODE_SHIFT_VAL          21
#define DPC_RD_SHIFT_VAL          12
#define DPC_RN_SHIFT_VAL          16
#define DPC_S_FLAG_SHIFT_VAL          20

#define LSR_BITS 0x20
#define ASR_BITS 0x40
#define ROR_BITS 0x60

#define AND_BITS 0
#define EOR_BITS 1
#define SUB_BITS 2
#define RSB_BITS 3
#define ADD_BITS 4
#define ORR_BITS 12
#define MOV_BITS 13
#define TST_BITS 8
#define TEQ_BITS 9
#define CMP_BITS 10

u_word handle_two_ops(char** op2, u_word instr_op2);
u_word data_processing(instruction_t *i);
u_word process_lsl(instruction_t *instruction);

#endif
