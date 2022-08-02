#ifndef BARREL_SHIFTER_H
#define BARREL_SHIFTER_H

#include "../cpsr.h"
#include "../../utils.h"
#include "../utils.h"

// shift types for data processing
typedef enum {
    LSL,
    LSR,
    ASR,
    ROR
} shiftType;

u_word shifter(state *state, bool *carry, bool i_flag, u_address operand2);

#endif
