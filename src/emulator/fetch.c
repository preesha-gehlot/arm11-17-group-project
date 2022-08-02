#include "fetch.h"

u_word fetch(state *state) {

    u_word pc = state -> registers[REG_PC];
    return getWordFromMem(pc, state, false);
}
