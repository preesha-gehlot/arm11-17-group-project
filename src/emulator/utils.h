#ifndef EMULATE_UTILS_H
#define EMULATE_UTILS_H

#include <stdlib.h>
#include <string.h>

#include "../definitions.h"
#include "gpio.h"
#include "definitions.h"

#define MSB_MASK 0x04000000u
#define SIGN_EXTEND_MASK 0xfc000000u

u_word sign_extend(u_word val);
u_word rotate_right(u_byte n, u_word val);
u_word getWordFromMem(u_word i, state *state, bool flipped);
void writeWordToMem(u_word val, state *state, u_address address);

#endif
