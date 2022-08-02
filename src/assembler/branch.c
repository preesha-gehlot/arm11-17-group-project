#include "branch.h"

// returns corresponding bits to the provided opcode
u_word findCond(opcode_t opcode){
    switch (opcode) {
        case BEQ: return BEQ_BITS;
        case BNE: return BNE_BITS;
        case BGE: return BGE_BITS;
        case BLT: return BLT_BITS;
        case BGT: return BGT_BITS;
        case BLE: return BLE_BITS;
        case B  : return B_BITS;
        default: errorAndExit("Unknown opcode at \"branch.c::findCond\".");
    }
}

u_word branch(assembler *ass){

    u_word result = 0;

    // gets relevant data from assembler struct
    instruction_t *inst = ass -> instructions -> array[ass -> instruction_pointer];
    symbolTable *symbolTable = ass -> table;
    u_address currentAddress = (ass -> instruction_pointer) * 4;

    // calculates offset bits
    char *target = inst -> ops[0];
    u_address targetAddress;
    if (target[0] == IMMEDIATE_CHAR){
        targetAddress = atoi(&target[1]);
    }else{
        targetAddress = st_lookup(symbolTable, target);
    }
    s_word offset = targetAddress - currentAddress - 8;
    offset = (offset >> 2) & 0xFFFFFF;

    // sets bits for the branch instruction
    set_bits(COND_SHIFT_VAL, findCond(inst -> opcode), &result);
    set_bits(BRANCH_BASE_SHIFT_VAL, BRANCH_BASE_BITS, &result);
    set_bits(0, offset, &result);

    return result;
}
