#ifndef DECODE_H
#define DECODE_H

#include "definitions.h"
#include "../utils.h"
#include "../extension/emulator/decode.h"

// masks to identify what type of instruction
#define MUL_MASK 0x0fc000f0u
#define DATA_MASK 0x0c000000u
#define S_DATA_MASK 0x04000000u
#define BRANCH_MASK 0x0a000000u

// functions to identify which type of instruction
#define IS_MUL(i)        ((MUL_MASK    & i) == 0x00000090u)
#define IS_DATA(i)       ((DATA_MASK   & i) == 0x00000000u)
#define IS_S_DATA(i)     ((S_DATA_MASK & i) == 0x04000000u)
#define IS_BRANCH(i)     ((BRANCH_MASK & i) == 0x0a000000u)

// masks for our multiply instructions
#define MUL_RD_MASK               0x000f0000u
#define MUL_RN_MASK               0x0000f000u
#define MUL_RS_MASK               0x00000f00u
#define MUL_RM_MASK               0x0000000fu
#define ACCUM_MASK                0x00200000u
#define SET_MASK                  0x00100000u

//masks for our branch instructions
#define OFFSET_BRANCH_MASK        0x00ffffffu

//masks for our data processing instructions
#define RN_MASK                   0x000f0000u
#define RD_MASK                   0x0000f000u
#define DPC_OPERAND2             0x00000fffu
#define OPCODE_MASK               0x01e00000u
#define I_MASK                    0x02000000u

decodedInstruction *decode(u_word instruction);

#endif
