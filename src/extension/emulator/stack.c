#include "stack.h"

void create_stack(state *state) {
    state -> registers[REG_SP] = STACK_STARTING_ADDRESS;
    state -> stack_size = 0;
}

void print_stack(state *state) {
  printf("---- STACK ----\n");
  u_address pointer = state -> registers[REG_SP];
  for (int i = state -> stack_size; i > 0; i--) {
    u_word val = getWordFromMem(pointer + WORD_SIZE, state, false);
    pointer += WORD_SIZE;
    printf("0x%08X\n", val);
  }
  printf("---------------\n");
}

u_word peek(state *state) {
  if (state -> stack_size == 0) errorAndExit("Stack is empty.");
  return getWordFromMem(state -> registers[REG_SP] + WORD_SIZE, state, false);
}

u_word pop(state *state) {
    u_word data_returned = peek(state);
    state -> registers[REG_SP] += WORD_SIZE;
    writeWordToMem(0, state, state -> registers[REG_SP]);
    state -> stack_size--;
    return data_returned;
}

void push(state *state, u_word data) {
    writeWordToMem(data, state, state -> registers[REG_SP]);
    state -> registers[REG_SP] -= WORD_SIZE;
    state -> stack_size++;
}
