#include "multiply.h"

u_word multiply(instruction_t *instructs) {

    u_word result = 0;

    // calculates and sets relevant bits
    set_bits(COND_SHIFT_VAL, MUL_COND_VAL, &result);

    u_word a_flag = instructs->opcode == MLA;
    set_bits(A_SHIFT_VAL, a_flag, &result);

    u_word rn = a_flag ? regToInt(instructs->ops[3]) : 0;
    set_bits(MUL_RN_SHIFT_VAL, rn, &result);

    set_bits(MUL_S_SHIFT_VAL, false, &result);
    set_bits(MUL_RD_SHIFT_VAL, regToInt(instructs->ops[0]), &result);


    set_bits(MUL_RS_SHIFT_VAL, regToInt(instructs->ops[2]), &result);
    set_bits(BITS_4_7_SHIFT_VAL, BITS_4_7_VAL, &result);
    set_bits(0, regToInt(instructs->ops[1]), &result);

    return result;
}
