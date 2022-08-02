#include "block_data_transfer.h"

// assume r13 has stack pointer value

// 1. initialise a stack in main
// 2. assign initial stack pointer to r13 in main
// 3. when stack pointer changes (ldm stm stack related)
// 4. change value in stack pointer AND R13

void execute_bdt(state *state) {

    block *instruction = state -> decoded -> instruction -> blockInstr;
    bool ldm = instruction -> ldm;
    bool stack_access = (instruction -> rn == 13);

    if (ldm){
      if (stack_access){
        for (int i = 0; i < 16; i++){
          if (instruction -> reg_list & (true << i)){
            state->registers[i] = pop(state);
          }
        }
      }else{
        u_address address = state -> registers[instruction -> rn];
        for (int i = 15; i > -1; i--){
          if ((instruction -> reg_list >> i) & 0x1){
            u_word mem_address = getWordFromMem(address, state, true);
            state -> registers[i] = mem_address;
            address += 4;
          }
        }
      }
    }

    // STM / push
    else{
      if (stack_access){
        for (int i = 15; i > -1; i--){
          if (instruction -> reg_list & (true << i)) {
            push(state, state->registers[i]);
          }
        }
      }else{
        u_address address = state -> registers[instruction -> rn];
        for (int i = 0; i <= 15; i++){
          if (instruction -> reg_list & (1 << i)) {
            state->memory[address++] = (state -> registers[i] & 0xff000000);
            state->memory[address++] = (state -> registers[i] & 0x00ff0000);
            state->memory[address++] = (state -> registers[i] & 0x0000ff00);
            state->memory[address] = (state -> registers[i] & 0x000000ff);
          }
        }
      }
    }
}


// int i = 0;
// int j = 0;
// while (i != 15){
  //   if (reg_list & 0x1){
    //     register[i] = rn[j];
    //     j++;
    //   }
    //   reg_list >> 1
    // }
    //IN STACK LDM IS pop
