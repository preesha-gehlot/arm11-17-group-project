#include <stdlib.h>
#include "emulator/execute/execute_swp.h"
#include "../emulator/definitions.h"
#include "../emulator/utils.h"

const decodedInstruction NULL_DECODED = {
  .i = NUL
};

const state INIT_STATE = {
  .memory = {0},
  .registers = {0},
  .endOfBinary = 0,
  .fetched = 0,
  .has_fetched = false,
  .decoded = NULL
};

int main(void){
    state *state1 = malloc(sizeof(state));
    *state1 = INIT_STATE;
    decodedInstruction *decodedInstr = malloc(sizeof(decodedInstr));
    decodedInstr->instruction = malloc(sizeof(instruction));

    state1->registers[4] = 0x64;
    state1->memory[100] = 0x11;
    state1->registers[5] = 0x5;

    decodedInstr->i = SWP;
    decodedInstr->cond = AL;
    singleDataSwap *swapInstr = malloc(sizeof(singleDataSwap));
    swapInstr->b_flag = 1;
    swapInstr->rn = 4;
    swapInstr->rd = 6;
    swapInstr->rm = 5;
    decodedInstr->instruction->swpInstr = swapInstr;
    state1->decoded = decodedInstr;

    execute_swp(state1);
    printf("%x ", state1->registers[swapInstr->rd]);
}
