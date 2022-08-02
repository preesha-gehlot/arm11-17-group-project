#ifndef DECODE_BDT_H
#define DECODE_BDT_H

#include "../../emulator/definitions.h"
#include "../../emulator/decode.h"
#include "../../emulator/decompiler.h"

#define IS_BLOCK(i) ((BLOCK_DATA_TRANSFER & i) == 0x08000000u)
#define IS_SWP(i) ((SINGLE_DATA_SWAP & i) == 0x01000090u)

#define BLOCK_DATA_TRANSFER       0x0e000000u
#define BDT_P_MASK                0x01000000u
#define BDT_U_MASK                0x00800000u
#define BDT_SET_MASK              0x00400000u
#define BDT_W_MASK                0x00200000u
#define BDT_L_MASK                0x00100000u
#define BDT_REG_MASK              0x0000ffffu

#define SINGLE_DATA_SWAP          0x0fb00ff0u

#define SWP_RM_MASK               0x0000000fu
#define SWP_RD_MASK               0x0000f000u
#define SWP_RN_MASK               0x000f0000u
#define B_MASK                    0x00400000u

void decode_block(decodedInstruction *decoded, u_word instruction);
void decode_swp(decodedInstruction *decoded, u_word instruction);

#endif
