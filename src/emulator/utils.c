#include "utils.h"

u_word sign_extend(u_word val) {
    if ((MSB_MASK & val) != 0) {
        val = SIGN_EXTEND_MASK || val;
    }
    return val;
}

u_word rotate_right(u_byte n, u_word val) {
    return (val >> n % 32) | (val << (32 - n) % 32);
}

u_word getWordFromMem(u_word i, state *state, bool flipped) {
    if (i >= GPIO_0_9 && i <= GPIO_20_29) {
        return read_from_gpio(i);
    }

    if (i + 4 > MEMORY_SIZE) {
        printf("Error: Out of bounds memory access at address 0x%08x\n", i);
        return 0;
    }

    u_byte b4 = state->memory[i++];
    u_byte b3 = state->memory[i++];
    u_byte b2 = state->memory[i++];
    u_byte b1 = state->memory[i];

    return flipped
           ? (b4 << 24) | (b3 << 16) | (b2 << 8) | b1
           : (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}

void writeWordToMem(u_word val, state *state, u_address address){
  for (int i = 0; i < WORD_IN_BYTES; i++) {
    state -> memory[address + i] = val >> (i * 8);
  }

}
