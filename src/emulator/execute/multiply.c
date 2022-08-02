#include "multiply.h"

bool execute_multiply(state *state) {

    multiply *instruction = state -> decoded -> instruction -> multiplyInstr;
    u_word registerRm = state -> registers[instruction -> rm];
    u_word registerRs = state -> registers[instruction -> rs];
    u_word registerRn = state -> registers[instruction -> rn];

    if (instruction -> accum_flag) {
        //If the accumulate flag is true, The multiply-accumulate instruction performs Rd=Rm*Rs+Rn
        state -> registers[instruction -> rd] = registerRm * registerRs + registerRn;
    } else {
        //The multiply instruction performs Rd=Rm*Rs. Rn is ignored.
        state -> registers[instruction -> rd] = registerRm * registerRs;
    }

    //Setting the CPSR flags
    if (instruction -> set_flag) {
      u_word rd = state -> registers[instruction -> rd];
      setCPSR(N, state, rd >> 31);
      if (rd == 0) {
        setCPSR(Z, state, 1);
      }
    }
    return true;
}
