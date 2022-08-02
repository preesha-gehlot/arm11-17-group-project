#include "decode.h"

void decode_block(decodedInstruction *decoded, u_word instruction) {
    block *blockInstruction = malloc(sizeof(block));
    decoded -> cond = (COND_MASK & instruction) >> 28;
    decoded -> i = BDT;
    blockInstruction -> p_flag = (BDT_P_MASK & instruction);
    blockInstruction -> u_flag = (BDT_U_MASK & instruction);
    blockInstruction -> s_flag = (BDT_SET_MASK & instruction);
    blockInstruction -> w_flag = (BDT_W_MASK & instruction);
    blockInstruction -> ldm = (BDT_L_MASK & instruction);
    blockInstruction -> rn = (RN_MASK & instruction) >> 16;
    blockInstruction -> reg_list = (BDT_REG_MASK & instruction);
    decoded -> instruction -> blockInstr = blockInstruction;
}

void decode_swp(decodedInstruction *decoded, u_word instruction) {
  singleDataSwap *swpInstruction = malloc(sizeof(singleDataSwap));
  decoded->cond = (COND_MASK & instruction) >> 28;
  decoded->i = SWP;
  swpInstruction -> b_flag = (B_MASK & instruction);
  swpInstruction -> rn = (SWP_RN_MASK & instruction) >> 16;
  swpInstruction -> rd = (SWP_RD_MASK & instruction) >> 12;
  swpInstruction -> rm = (SWP_RM_MASK & instruction);
  decoded -> instruction -> swpInstr = swpInstruction;
}
