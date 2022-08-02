#include "single_data_transfer.h"

u_word get_offset(state *state) {
    singleDataTransfer *instruction = state -> decoded -> instruction -> SDTInstr;
    bool carry;
    return shifter(state, &carry, !instruction -> i_flag, instruction -> offset);
}

u_word change_base_register(state *state) {
    singleDataTransfer *instruction = state -> decoded -> instruction -> SDTInstr;
    u_word offset = get_offset(state);
    return instruction -> u_flag
      ? state -> registers[instruction -> rn] + offset
      : state -> registers[instruction -> rn] - offset;
}

void execute_sdt(state *state) {

    singleDataTransfer *instruction = state -> decoded -> instruction -> SDTInstr;
    u_word memory_access;

    //pre-indexing
    if (instruction -> p_flag) {
        memory_access = change_base_register(state);
    } else {
        //post-indexing
        memory_access = state -> registers[instruction -> rn];
        state -> registers[instruction -> rn] = change_base_register(state);
    }

    //load from memory
    if (instruction -> l_flag == 1) {
        *(state -> registers + instruction -> rd) = getWordFromMem(memory_access, state, 0);
    } else {
        if (GPIO_0_9 <= memory_access && memory_access <= GPIO_CLEAR + GPIO_CLEAR_CONTROL_SIZE) {
          set_gpio(memory_access);
        } else {
          //store into memory
          state->memory[memory_access++] = (u_byte) *(state -> registers + instruction -> rd);
          state->memory[memory_access++] = (u_byte) (*(state -> registers + instruction -> rd) >> 8);
          state->memory[memory_access++] = (u_byte) (*(state -> registers + instruction -> rd) >> 16);
          state->memory[memory_access] = (u_byte) (*(state -> registers + instruction -> rd) >> 24);
        }
    }
}
