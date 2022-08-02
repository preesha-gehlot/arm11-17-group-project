#include "utils.h"

void errorAndExit(char errorMessage[]) {
    fprintf(stderr, "%s\n", errorMessage);
    exit(EXIT_FAILURE);
}

// shifts the bits of a word into little endian
u_word to_little_endian(u_word val) {
  u_byte b1, b2, b3, b4;
  b1 = val;
  b2 = val >> BYTE_2_SHIFT_VAL;
  b3 = val >> BYTE_3_SHIFT_VAL;
  b4 = val >> BYTE_4_SHIFT_VAL;
  return b1 >> BYTE_4_SHIFT_VAL | b2 >> BYTE_3_SHIFT_VAL | b3 >> BYTE_2_SHIFT_VAL | b4;
}
