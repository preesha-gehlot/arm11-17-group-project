#include "decompiler.h"

void printOperand2(bool i_flag, u_address op, bool negative) {

  if (op == 0) {
    if (i_flag) {
      printf("#0");
    } else {
      printf("r0");
    }
    return;
  }

  if (i_flag) {
    u_word operand2 = rotate_right(2*(op >> 8), (u_byte) op);
    if (negative) {
      printf("#-%d", operand2);
    } else {
      printf("#%d", operand2);
    }
  } else {
    u_byte shift = op >> 4;
    u_byte rm = op & 0xf;

    char* shiftNames[] = {"LSL", "LSR", "ASR", "ROR"};
    char* shiftName = shiftNames[(shift >> 1) & 0x3];

    if ((bool) shift) {
      u_byte rs = shift >> 4;
      if (rs) {
        printf("(%s r%d r%d)", shiftName, rm, rs);
      } else {
        printf("r%d", rm);
      }
    } else {
      u_byte shiftVal = shift >> 3;
      if (shiftVal) {
        printf("(%s r%d %d)", shiftName, rm, shiftVal);
      } else {
        printf("r%d", rm);
      }
    }
  }
}

void printDPC(dataProcessing *dpc) {
  switch (dpc -> opcode) {
    case AND:
      printf("and r%d r%d ", dpc -> rd, dpc -> rn);
      printOperand2(dpc -> i_flag, dpc -> operand2, false);
      break;
    case EOR:
      printf("eor r%d r%d ", dpc -> rd, dpc -> rn);
      printOperand2(dpc -> i_flag, dpc -> operand2, false);
      break;
    case SUB:
      printf("sub r%d r%d ", dpc -> rd, dpc -> rn);
      printOperand2(dpc -> i_flag, dpc -> operand2, false);
      break;
    case RSB:
      printf("rsb r%d ", dpc -> rd);
      printOperand2(dpc -> i_flag, dpc -> operand2, false);
      printf(" r%d", dpc -> rn);
      break;
    case ADD:
      printf("add r%d r%d ", dpc -> rd, dpc -> rn);
      printOperand2(dpc -> i_flag, dpc -> operand2, false);
      break;
    case TST:
      printf("tst r%d ", dpc -> rn);
      printOperand2(dpc -> i_flag, dpc -> operand2, false);
      break;
    case TEQ:
      printf("teq r%d ", dpc -> rn);
      printOperand2(dpc -> i_flag, dpc -> operand2, false);
      break;
    case CMP:
      printf("cmp r%d ", dpc -> rn);
      printOperand2(dpc -> i_flag, dpc -> operand2, false);
      break;
    case ORR:
      printf("orr r%d r%d ", dpc -> rd, dpc -> rn);
      printOperand2(dpc -> i_flag, dpc -> operand2, false);
      break;
    case MOV:
      printf("mov r%d ", dpc -> rd);
      printOperand2(dpc -> i_flag, dpc -> operand2, false);
      break;
  }
}

void printMUL(multiply *mul) {
  if (mul -> accum_flag) {
    printf("mla r%d r%d r%d r%d", mul -> rd, mul -> rm, mul -> rs, mul -> rn);
  } else {
    printf("mul r%d r%d r%d", mul -> rd, mul -> rm, mul -> rs);
  }
}

void printSDT(singleDataTransfer *sdt) {
  if (sdt -> l_flag) {
    printf("ldr r%d [r%d,", sdt -> rd, sdt -> rn);
    printOperand2(!sdt -> i_flag, sdt -> offset, !sdt -> u_flag);
    printf("]");
  } else {
    printf("str r%d [r%d,", sdt -> rd, sdt -> rn);
    printOperand2(!sdt -> i_flag, sdt -> offset, !sdt -> u_flag);
    printf("]");
  }
}

void printBRA(branch *bra) {
  printf("b PC+%d", (s_word) bra -> offset);
}

void printCondition(decodedInstruction *decoded) {
  if (decoded -> cond != 14) printf(" [cond = %d]\n", decoded -> cond);
  else printf("\n");
}

void printBDT(block *decoded) {
  char *type = decoded -> ldm ? "ldm" : "stm";
  char p = decoded -> p_flag ? 'e' : 'f';
  char u = decoded -> u_flag ? 'd' : 'a';
  printf("%s%c%c ", type, p, u);
  printf("r%d {", decoded -> rn);
  bool first = true;
  for (int i = 0; i < 16; i++) {
    if (decoded -> reg_list & (1 << i)) {
      if (!first) printf(", ");
      first = false;
      printf("r%d", i);
    }
  }
  printf("}");
}

void printSWP(singleDataSwap *swap) {
  printf("swp");
  if (swap -> b_flag) printf("b");
  printf(" r%d r%d [r%d]", swap -> rd, swap -> rm, swap -> rn);
}

void printDecoded(state *state) {
  decodedInstruction *decoded = state -> decoded;
  switch(decoded -> i) {
    case DPC:
      printDPC(decoded -> instruction -> dataProcessingInstr);
      break;
    case MUL:
      printMUL(decoded -> instruction -> multiplyInstr);
      break;
    case SDT:
      printSDT(decoded -> instruction -> SDTInstr);
      break;
    case BRA:
      printBRA(decoded -> instruction -> branchInstr);
      break;
    case HLT:
      printf("HALT\n");
      return;
    case BDT:
      printBDT(decoded -> instruction -> blockInstr);
      break;
    case SWP:
      printSWP(decoded -> instruction -> swpInstr);
      break;
    case NUL:
      return;
  }
  printCondition(decoded);
}
