#include "data_processing.h"

void updateCPSRLogical(state *state, bool carry) {
  if (state -> decoded -> instruction -> dataProcessingInstr -> set_flag) {
    setCPSR(C, state, carry);
  }
}

void updateCPSRSubtraction(state *state, u_word x, u_word y) {
  if (state -> decoded -> instruction -> dataProcessingInstr -> set_flag) {
    setCPSR(C, state, x >= y);
  }
}

bool execute_data_processing(state *state) {

    bool carry;
    dataProcessing *instruction = state -> decoded -> instruction -> dataProcessingInstr;
    u_word operand2 = shifter(state, &carry, instruction -> i_flag, instruction -> operand2);
    opcode opcode = instruction -> opcode;
    u_word rn = state -> registers[instruction -> rn];

    u_word result;

    switch (opcode) {
        // Rn AND operand2
        case AND:
            result = rn & operand2;
            state -> registers[instruction -> rd] = result;
            updateCPSRLogical(state, carry);
            break;
        // Rn EOR operand2
        case EOR:
            result = rn ^ operand2;
            state -> registers[instruction -> rd] = result;
            updateCPSRLogical(state, carry);
            break;
        // Rn - operand2
        case SUB:
            result = rn - operand2;
            state -> registers[instruction -> rd] = result;
            updateCPSRSubtraction(state, rn, operand2);
            break;
        // operand2 - Rn
        case RSB:
            result = operand2 - rn;
            state -> registers[instruction -> rd] = result;
            updateCPSRSubtraction(state, operand2, rn);
            break;
        // Rn + operand2
        case ADD:
            result = rn + operand2;
            state -> registers[instruction -> rd] = result;
            if (instruction -> set_flag) {
              setCPSR(C, state, result > WORD_MAX);
            }
            break;
        // as and but result not written
        case TST:
            result = rn & operand2;
            updateCPSRLogical(state, carry);
            break;
        // as eor but result not written
        case TEQ:
            result = rn ^ operand2;
            updateCPSRLogical(state, carry);
            break;
        // as sub but result not written
        case CMP:
            result = rn - operand2;
            updateCPSRSubtraction(state, rn, operand2);
            break;
        // Rn OR operand2
        case ORR:
            result = rn | operand2;
            state -> registers[instruction -> rd] = result;
            break;
        // operand2 (Rn is ignored)
        case MOV:
            result = operand2;
            state -> registers[instruction -> rd] = result;
            updateCPSRLogical(state, carry);
            break;
        default:
            errorAndExit("Unknown data processing instruction.");
    }

    if (instruction -> set_flag) {
      setCPSR(Z, state, result == 0);
      setCPSR(N, state, result >> 31);
    }

    return true;
}
