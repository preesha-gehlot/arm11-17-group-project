#include "barrel_shifter.h"

u_word shifter(state *state, bool *carry, bool i_flag, u_address operand2) {

    if (i_flag) {
        //if i_flag = 0 shift operations are applied to the value held in register Rm
        int n = (operand2 >> 8);
        return rotate_right(n * 2, (u_byte) operand2);
    } else {
        u_word rm = state->registers[operand2 & 0xf];
        u_byte shift = operand2 >> 4;

        u_byte shiftVal;
        if (shift & 0x1) {
            //shift by register amount
            shiftVal = state->registers[shift >> 4];
        } else {
            //shift by constant amount
            shiftVal = shift >> 3;
        }

        shiftType shiftType = (shift >> 1) & 0x3;
        switch (shiftType) {
            //00 logical left (lsl) Moves each bit to the left by the specified amount.
            case LSL:
                *carry = (bool) (rm >> (31 - shiftVal));
                return rm << shiftVal;
            //01 logical right (lsr) Moves each bit to the right by the specified amount.
            case LSR:
                *carry = (rm >> (shiftVal - 1)) & 1;
                return rm >> shiftVal;
            //10 arithmetic right (asr) As lsr but preserves the sign bit; used for 2's complement operations.
            case ASR:
                *carry = (rm >> (shiftVal - 1)) & 1;
                return ((s_word) rm) >> shiftVal;
            //11 rotate right (ror) Rotate cyclically with bit 0 shifting into bit 31.
            case ROR:
                *carry = (rm >> (shiftVal - 1)) & 1;
                return rotate_right(shiftVal, rm);
            default:
                errorAndExit("Unknown shift type.");
                return;
        }
    }
}
