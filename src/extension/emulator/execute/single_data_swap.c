#include "single_data_swap.h"

void execute_swp(state *state){
  singleDataSwap *swpInstruction = state -> decoded->instruction->swpInstr;
  u_address rn = state -> registers[swpInstruction->rn];
  u_word rm = state -> registers[swpInstruction->rm];
  if (swpInstruction -> b_flag){
    // if b flag is 1 we swap byte quantity
    state -> registers[swpInstruction->rd] = state -> memory[rn];
    state -> memory[rn] = rm;

  }else{
    state -> registers[swpInstruction->rd] = getWordFromMem(rn, state, false);
    writeWordToMem(rm, state, rn);
  }
}
