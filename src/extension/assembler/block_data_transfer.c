#include "block_data_transfer.h"

void set_l_p_u_flag(u_word *result, bool l_flag, bool p_flag, bool u_flag) {
    set_bits(BDT_L_SHIFT_VAL, l_flag, result);
    set_bits(BDT_P_SHIFT_VAL, p_flag, result);
    set_bits(BDT_U_SHIFT_VAL, u_flag, result);
}

void cons_registers(char *registers, u_word *result) {
    char *reg_max = registers;
    char *reg_min = strsep(&reg_max, "-");
    for (int i = regToInt(reg_min); i <= regToInt(reg_max); i++) {
      set_bits(i, true, result);
    }
}

u_word blockDataTransfer(instruction_t *instruction) {

    u_word result = 0;
    set_bits(COND_SHIFT_VAL, BDT_COND_VAL, &result);
    set_bits(BDT_BITS_27_26_SHIFT_VAL, BDT_BITS_27_26, &result);

    switch (instruction->opcode) {
        case LDMED:
            set_l_p_u_flag(&result, 1, 1, 1);
            break;
        case LDMFD:
            set_l_p_u_flag(&result, 1, 0, 1);
            break;
        case LDMEA:
            set_l_p_u_flag(&result, 1, 1, 0);
            break;
        case LDMFA:
            set_l_p_u_flag(&result, 1, 0, 0);
            break;
        case STMFA:
            set_l_p_u_flag(&result, 0, 1, 1);
            break;
        case STMEA:
            set_l_p_u_flag(&result, 0, 0, 1);
            break;
        case STMFD:
            set_l_p_u_flag(&result, 0, 1, 0);
            break;
        case STMED:
            set_l_p_u_flag(&result, 0, 0, 0);
            break;
    }

    //operand 1 contains the base register and can also have '!' char
    char *operand1 = instruction->ops[0];
    bool w_flag = strchr(operand1, '!') != NULL;
    set_bits(BDT_W_SHIFT_VAL, w_flag , &result);

    if (strstr(operand1, "sp") != NULL) {
        set_bits(BDT_RN_SHIFT_VAL, STACK_POINTER_REGISTER, &result);
    } else {
        set_bits(BDT_RN_SHIFT_VAL, regToInt(operand1), &result);
    }

    //operand 2 contains the register list and can also have '^' char
    char *operand2 = instruction->ops[1];
    bool s_flag = strchr(operand2, '^') != NULL; // unused flag
    set_bits(BDT_S_SHIFT_VAL, s_flag , &result);

    int size = count_commas(operand2) + 1;

    char *to_split = &operand2[1];
    to_split[strlen(to_split) - 1] = END_CHAR;

    char *list_of_registers[size];
    split_ops(to_split, list_of_registers);

    for (int i = 0; i < size; i++) {
        char *reg = list_of_registers[i];
        if (strchr(reg, SUBTRACT_CHAR)) {
            cons_registers(reg, &result);
        } else {
            set_bits(regToInt(reg), true, &result);
        }
    }

    return result;
}

u_word process_bdt_alias(instruction_t *instruction, opcode_t opcode) {
  instruction_t *temp = malloc(sizeof(instruction_t));
  temp -> label = instruction -> label;
  temp -> has_label = instruction -> has_label;
  temp -> opcode = opcode;
  char op[] = "sp!";
  temp -> ops[0] = op;
  temp -> ops[1] = instruction -> ops[0];
  temp -> no_of_ops = 2;
  u_word out = blockDataTransfer(temp);
  free(temp);
  return out;
}

u_word process_pop(instruction_t *instruction) {
  return process_bdt_alias(instruction, LDMED);
}

u_word process_push(instruction_t *instruction) {
  return process_bdt_alias(instruction, STMED);
}
