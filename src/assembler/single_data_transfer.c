#include "single_data_transfer.h"

// calculates offset to value stored at end of assembly file
u_address offset_to_stored(u_word val, assembler *assembler) {
    // adds val to the values dynamic array to be stored to the end of the file
    word_array_add(assembler -> values, val);

    // computes offset from instruction address, no of instructions and no of values
    u_address newAddress = (assembler -> instructions -> used) * WORD_IN_BYTES - 8;
    newAddress -= (assembler -> instruction_pointer) * WORD_IN_BYTES;
    newAddress += (assembler -> values -> used - 1) * WORD_IN_BYTES;
    return newAddress;
}

// converts ldr instruction into mov by delegating to dataprocessing
u_word convert_to_mov(instruction_t *instruction) {
    // updates instruction data to be a dataprocessing instruction
    instruction->opcode = MOV;
    u_word immediate = strtol(&instruction -> ops[1][1], NULL, 0);
    sprintf(instruction -> ops[1], "%c%d", IMMEDIATE_CHAR, immediate);
    return data_processing(instruction);
}

// computes and sets bits for expression or treats as a mov
void process_expression(u_word *result, instruction_t *instruction, assembler *assembler) {
  u_word expression = toInt(&instruction->ops[1][1]);
    //checks if the value is small enough in order to use a mov
    if (expression <= MAX_FOR_MOV) {
      // delegates to convert_to_mov
      *result = convert_to_mov(instruction);
    } else {
      // computes and sets the bits for sdt instruction
      set_bits(SDT_P_SHIFT_VAL, true, result); // P flag
      set_bits(SDT_U_SHIFT_VAL, true, result); // U flag
      set_bits(0, offset_to_stored(expression, assembler), result);
      set_bits(SDT_RN_SHIFT_VAL, REG_PC, result); // Rn
    }
}

// computes and sets the bits for pre indexing instructions (P_FLAG = 1)
void pre_indexing(u_word *result, instruction_t *instruction, assembler *assembler) {
  char *operand2 = instruction->ops[1];
  //eliminate the '[' and copies the value of the pointer into new variable
  char *to_split = &operand2[1];
  //eliminate the ']'
  to_split[strlen(to_split) - 1] = END_CHAR;

  // splits operands within '[]' into seperate ops
  char *operands2[3] = {0};
  int i = split_ops(to_split, operands2);

  // sets bits calculated from the operands within '[]'
  set_bits(SDT_RN_SHIFT_VAL, regToInt(operands2[0]), result); // Rn
  set_bits(SDT_P_SHIFT_VAL, true, result); // P flag

  // based on the number of operands we then use a switch case to see which
  // type of pre indexed address it is and set the relevant bits in each case
  bool u_flag = 0;
  switch (i) {
      case 1:
          set_bits(SDT_U_SHIFT_VAL, true, result);
          // offset = 0;
          break;
      case 2:
          set_bits(SDT_I_SHIFT_VAL, operands2[1][0] != IMMEDIATE_CHAR, result);
          u_flag = operands2[1][1] != SUBTRACT_CHAR;
          set_bits(SDT_U_SHIFT_VAL, u_flag, result);
          set_bits(0,toInt(&operands2[1][1 + (u_flag ? 0 : 1)]), result);
          break;
      case 3:
          set_bits(SDT_I_SHIFT_VAL, true, result);
          u_flag = operands2[1][1] != SUBTRACT_CHAR;
          set_bits(SDT_U_SHIFT_VAL, u_flag, result);
          u_word offset = toInt(&operands2[1][1 + (u_flag ? 0 : 1)]);
          set_bits(0, handle_two_ops(&operands2[1], offset), result);
          break;
  }
  // frees the memory allocated when splitting the operands within the '[]'
  for (int i = 0; i < 3; i++) {
    free(operands2[i]);
  }
}

// computes and sets the bits for post indexing instructions (P_FLAG = 0)
void post_indexing(u_word *result, instruction_t *instruction, assembler *assembler) {
  char *operand2 = instruction->ops[1];
  //eliminate the '['
  operand2 = &operand2[1];
  //eliminate the ']'
  operand2[strlen(operand2) - 1] = END_CHAR;

  // computes and sets the U flag
  bool u_flag = instruction->ops[2][1] != SUBTRACT_CHAR;
  set_bits(SDT_U_SHIFT_VAL, u_flag, result);

  // computes and sets relevant bits
  set_bits(SDT_P_SHIFT_VAL, false, result);
  set_bits(SDT_RN_SHIFT_VAL, regToInt(&operand2[0]), result);
  set_bits(0, toInt(&instruction->ops[2][1 + (u_flag ? 0 : 1)]), result);

  // computes and sets offset and I flag bits
  if (instruction->ops[2][0] != IMMEDIATE_CHAR){

    u_word offset = toInt(&instruction->ops[2][1 + (u_flag ? 0 : 1)]);
    bool i_flag = instruction -> no_of_ops != 4;
    if (!i_flag) {
      offset = handle_two_ops(&instruction -> ops[2], offset);
    }

    set_bits(0, offset, result);
    set_bits(SDT_I_SHIFT_VAL, i_flag, result);
  }
}

//
u_word single_data_transfer(assembler *assembler) {
  instruction_t *instruction = assembler->instructions->array[assembler->instruction_pointer];
  u_word result = 0;

  // computes and sets relevant bits
  set_bits(COND_SHIFT_VAL, SDT_COND_VAL, &result);
  set_bits(SDT_BITS_27_26_SHIFT_VAL, SDT_BITS_27_26, &result);
  set_bits(SDT_I_SHIFT_VAL, false, &result);
  set_bits(SDT_L_SHIFT_VAL, instruction->opcode == LDR, &result);
  set_bits(SDT_RD_SHIFT_VAL, regToInt(instruction->ops[0]), &result);

  // delegates to relevant functions depending on instruction type
  if (IS_EXPRESSION()) {
    process_expression(&result, instruction, assembler);
  } else if (IS_PRE_INDEXING()){
    pre_indexing(&result, instruction, assembler);
  } else {
    post_indexing(&result, instruction, assembler);
  }
  return result;
}
