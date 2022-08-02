#include "branch.h"

bool execute_branch(state *state) {

    branch *instruction = state -> decoded -> instruction -> branchInstr;
    u_word offset;
    bool negative = instruction -> offset >> 23;
    if (negative) {
      offset = (~instruction -> offset) + 1;
      offset &= 0xFFFFFF;
    } else {
      offset = instruction -> offset;
    }
    u_word sign_extended_offset = sign_extend(offset << 2);
    if (negative) {
      state -> registers[REG_PC] -= sign_extended_offset;
    } else {
      state -> registers[REG_PC] += sign_extended_offset;
    }
    state -> has_fetched = false;
    return true;

}
