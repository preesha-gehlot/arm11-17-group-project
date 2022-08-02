#include "single_data_swap.h"

// returns corresponding bits to the provided opcode
u_byte findSWPCond(opcode_t opcode){
    switch (opcode) {
        case SWPEQ:
        case SWPEQB: return EQ;
        case SWPNE:
        case SWPNEB: return NE;
        case SWPGE:
        case SWPGEB: return GE;
        case SWPLT:
        case SWPLTB: return LT;
        case SWPGT:
        case SWPGTB: return GT;
        case SWPLE:
        case SWPLEB: return LE;
        case SWP:
        case SWPB: return AL;
        default: errorAndExit("Unknown opcode at \"single_data_swap.c::findCond\".");
    }
}

u_word single_data_swap(instruction_t *instruction){

  u_word result = 0;

  set_bits(COND_SHIFT_VAL, findSWPCond(instruction -> opcode), &result);
  set_bits(0, SWP_BASE_VAL, &result);
  set_bits(BDT_B_FLAG_SHIFT_VAL, instruction->opcode == SWPB, &result);
  set_bits(BDT_RD_SHIFT_VAL, regToInt(instruction->ops[0]), &result);
  set_bits(BDT_RM_SHIFT_VAL, regToInt(instruction->ops[1]), &result);

  char *operand3 = instruction->ops[2];
  //eliminate the '[' and copies the value of the pointer into new variable
  char *to_split = &operand3[1];
  //eliminate the ']'
  to_split[strlen(to_split) - 1] = END_CHAR;

  set_bits(BDT_RN_SHIFT_VAL, regToInt(to_split), &result);

  return result;
}
