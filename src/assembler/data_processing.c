#include "data_processing.h"

// rotates val left by n bits
u_word rotate_left(u_word val, int n) {
  return (val << n) | (val >> (WORD_IN_BITS - n));
}

// rotates immediate till smaller than 0xFF and saves how many it was shifted by
u_address rotate_immediate(u_word val) {
  u_byte i = 0;
  while (val > MAX_FOR_MOV && i < MAX_SHIFTS) {
    val = rotate_left(val, 2);
    i++;
  }
  if (val <= MAX_FOR_MOV) return i << IMMEDIATE_SHIFT_VAL | (u_byte) val;
  else errorAndExit("Value too large at \"data_processing.c::rotate_immediate\".");
}

// returns corresponding bits to the provided opcode
u_byte findOpcode(opcode_t op){
    switch (op) {
        case AND: return AND_BITS;
        case EOR: return EOR_BITS;
        case SUB: return SUB_BITS;
        case RSB: return RSB_BITS;
        case ADD: return ADD_BITS;
        case ORR: return ORR_BITS;
        case MOV: return MOV_BITS;
        case TST: return TST_BITS;
        case TEQ: return TEQ_BITS;
        case CMP: return CMP_BITS;
        default: errorAndExit("Unknown opcode at \"data_processing.c::findCond\".");
    }
}

// converts a string into an expression given a max size
u_word toExpression(char* op_2, u_byte max_size){
    u_word instr_op2 = toInt(op_2);
    if(instr_op2 > max_size) {
      return rotate_immediate(instr_op2);
    } else {
      return instr_op2;
    }
}

// returns bits for a dpc instruction with two extra operands
u_word handle_two_ops(char** op2, u_word instr_op2) {
  // makes copies of the pointers for each string
  char *sub_op1 = op2[0];
  char *sub_op2 = op2[1];

  // separates sub_op2 by " " (SHIFT_DELIMITER)
  char *shift_type = strsep(&sub_op2, SHIFT_DELIMITER);

  // calculates bits for operand2
  u_word operand2;
  if (sub_op2[0] == IMMEDIATE_CHAR) {
    // if an immediate, get the value
    operand2 = toInt(&sub_op2[1]) << OP2_IMMEDIATE_SHIFT_VAL;
  } else {
    u_word rs = regToInt(sub_op2) << RS_SHIFT_VAL;
    operand2 = rs | SHIFT_BY_REG_FLAG_BITS;
  }

  // calculates and sets bits based on shift type
  if (!strcmp(shift_type, "lsr")){
      return instr_op2 | LSR_BITS | operand2; // binary: 0010 0000
  } else if (!strcmp(shift_type, "asr")){
    return instr_op2 | ASR_BITS | operand2; // binary: 0100 0000
  } else if (!strcmp(shift_type, "ror")){
      return instr_op2 | ROR_BITS | operand2; // binary: 0110 0000
  } else if (!strcmp(shift_type, "lsl")) {
    return instr_op2 | operand2; // binary: 0000 0000
  } else errorAndExit("Unknown shift type at \"assemble_dataprocessing.c::handle_two_ops\".");
}

// calculates bits based on remaining operands (n operands)
u_word shiftOrReg(char** op2, int n){
    u_word instr_op2 = regToInt(op2[0]);
    // delegates to relevant functions
    switch (n) {
      case 1: return instr_op2;
      case 2: return handle_two_ops(op2, instr_op2);
      default: errorAndExit("Too many operands at \"assemble_dataprocessing.c::shiftOrReg\".");
    }
}

// delegates to relevant functions to calculate operand2 bits
u_word getOperand(char** op2, int n){
    if (op2[0][0] == IMMEDIATE_CHAR){
        return toExpression(&op2[0][1], MAX_FOR_MOV) | I_FLAG_VAL;
    }
    return shiftOrReg(op2, n);
}

u_word data_processing(instruction_t *i){

    // initializes variables containing relevant bits
    u_word cond = DPC_COND_VAL << COND_SHIFT_VAL;
    u_word opcode = findOpcode(i->opcode) << OPCODE_SHIFT_VAL;
    u_word operand2 = 0;
    u_word rd = 0;
    u_word rn = 0;
    u_word s_flag = false;
    // populates the bits unique to certain opcodes
    switch (i->opcode) {
      case AND:
      case EOR:
      case SUB:
      case RSB:
      case ADD:
      case ORR:
      // compute bits for "instructions that compute results"
            rd = regToInt(i->ops[0]) << DPC_RD_SHIFT_VAL;
            rn = regToInt(i->ops[1]) << DPC_RN_SHIFT_VAL;
            operand2 = getOperand(&i->ops[2], i -> no_of_ops - 2);
            return cond | opcode | rd | rn | operand2;
            break;
        case MOV:
        // compute bits for "single operand assignment"
            rd = regToInt(i->ops[0]) << DPC_RD_SHIFT_VAL;
            operand2 = getOperand(&i->ops[1], i -> no_of_ops - 1);
            return cond | opcode | rd | operand2;
            break;
        case TST:
        case TEQ:
        case CMP:
        // compute bits for "instructions that do not compute results, but do set the CPSR flags"
            rn = regToInt(i->ops[0]) << DPC_RN_SHIFT_VAL;
            operand2 = getOperand(&i->ops[1], i -> no_of_ops - 1);
            s_flag = true << DPC_S_FLAG_SHIFT_VAL;
            return cond | opcode | s_flag | rn | operand2;
            break;
    }
}

u_word process_lsl(instruction_t *instruction) {
  instruction_t *temp = malloc(sizeof(instruction_t));
  temp -> label = instruction -> label;
  temp -> has_label = instruction -> has_label;
  temp -> opcode = MOV;
  // char *rn = instruction -> ops[0];
  char *exp = instruction -> ops[1];
  temp -> ops[0] = temp -> ops[1] = instruction -> ops[0];
  char op3[4 + strlen(exp)];
  sprintf(op3, "%s %s", "lsl", exp);
  temp -> ops[2] = op3;
  temp -> no_of_ops = 3;
  u_word out = data_processing(temp);
  free(temp);
  return out;
}
