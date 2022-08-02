#include "decode.h"

void decode_multiply(decodedInstruction *decoded, u_word instruction) {
    multiply *multiplyInstruction = malloc(sizeof(multiply));
    decoded -> i = MUL;
    decoded -> cond = (COND_MASK & instruction) >> 28;
    multiplyInstruction -> accum_flag = (ACCUM_MASK & instruction) >> 21;
    multiplyInstruction -> set_flag = (SET_MASK & instruction) >> 20;
    multiplyInstruction -> rm = MUL_RM_MASK & instruction;
    multiplyInstruction -> rs = (MUL_RS_MASK & instruction) >> 8;
    multiplyInstruction -> rn = (MUL_RN_MASK & instruction) >> 12;
    multiplyInstruction -> rd = (MUL_RD_MASK & instruction) >> 16;
    decoded -> instruction -> multiplyInstr = multiplyInstruction;
}

void decode_dpc(decodedInstruction *decoded, u_word instruction) {
    dataProcessing *dataProcInstruction = malloc(sizeof(dataProcessing));
    decoded -> i = DPC;
    decoded -> cond = (COND_MASK & instruction) >> 28;
    dataProcInstruction -> rn = (RN_MASK & instruction) >> 16;
    dataProcInstruction -> rd = (RD_MASK & instruction) >> 12;
    dataProcInstruction -> operand2 = DPC_OPERAND2 & instruction;
    dataProcInstruction -> opcode = (OPCODE_MASK & instruction) >> 21;
    dataProcInstruction -> i_flag = (I_MASK & instruction) >> 25;
    dataProcInstruction -> set_flag = (SET_MASK & instruction) >> 20;
    decoded -> instruction -> dataProcessingInstr = dataProcInstruction;
}

void decode_sdt(decodedInstruction *decoded, u_word instruction) {
    singleDataTransfer *SDTInstruction = malloc(sizeof(singleDataTransfer));
    decoded -> i = SDT;
    decoded -> cond = (COND_MASK & instruction) >> 28;
    SDTInstruction -> i_flag = (I_MASK & instruction) >> 25;
    SDTInstruction -> p_flag = (P_MASK & instruction) >> 24;
    SDTInstruction -> u_flag = (U_MASK & instruction) >> 23;
    SDTInstruction -> l_flag = (L_MASK & instruction) >> 20;
    SDTInstruction -> rn = (RN_MASK & instruction) >> 16;
    SDTInstruction -> rd = (RD_MASK & instruction) >> 12;
    SDTInstruction -> offset = (OFFSET_SDT_MASK & instruction);
    decoded -> instruction -> SDTInstr = SDTInstruction;
}

void decode_branch(decodedInstruction *decoded, u_word instruction) {
    branch *branchInstruction = malloc(sizeof(branch));
    decoded -> i = BRA;
    decoded -> cond = (COND_MASK & instruction) >> 28;
    branchInstruction -> offset = OFFSET_BRANCH_MASK & instruction;
    decoded -> instruction -> branchInstr = branchInstruction;
}

decodedInstruction *decode(u_word instruction) {
    decodedInstruction *decoded = malloc(sizeof(decodedInstruction));
    decoded -> instruction = malloc(sizeof(instruction));
    void (*decode_ptr)(decodedInstruction *, u_word);
    if (instruction == 0) {
        decoded -> i = HLT;
        return decoded;
    } else if (IS_BLOCK(instruction)) {
      decode_ptr = &decode_block;
    } else if (IS_SWP(instruction)) {
      decode_ptr = &decode_swp;
    } else if (IS_MUL(instruction)) {
      decode_ptr = &decode_multiply;
    } else if (IS_DATA(instruction)) {
      decode_ptr = &decode_dpc;
    } else if (IS_S_DATA(instruction)) {
      decode_ptr = &decode_sdt;
    } else if (IS_BRANCH(instruction)) {
      decode_ptr = &decode_branch;
    } else errorAndExit("Unknown instruction type.");

    decode_ptr(decoded, instruction);
    return decoded;
}
