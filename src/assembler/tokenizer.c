#include "tokenizer.h"

// array of all opcodes used to convert from string to enum opcode_t
const char* opcodes[] = {
  "add",
  "sub",
  "rsb",
  "and",
  "eor",
  "mov",
  "tst",
  "teq",
  "cmp",
  "orr",
  "mul",
  "mla",
  "ldr",
  "str",
  "beq",
  "bne",
  "bge",
  "blt",
  "bgt",
  "ble",
  "b",
  "lsl",
  "andeq",
  "ldmed",
  "ldmfd",
  "ldmea",
  "ldmfa",
  "stmfa",
  "stmea",
  "stmfd",
  "stmed",
  "pop",
  "push",
  "swp",
  "swpb"
};

static const instruction_t INIT_INSTRUCTION = {
  .opcode = NONE,
  .ops = {0},
  .no_of_ops = 0,
  .has_label = false
};

// gets opcode from a string
opcode_t get_opcode(char *str) {
  for (int i = 0; i < NO_OPCODES; i++) {
    if (!strcmp(opcodes[i], str)) return i;
  }
  return NONE;
}

// splits a string at break delimiters provided (i.e. '[]', '{}')
bool split_break(char **string, char *token, const char start_delim, const char *end_delim) {
  if ((*string)[0] == start_delim) {
    char *sub_op = strsep(string, end_delim);
    sprintf(token, "%s%s", sub_op, end_delim);
    return false;
  } else return true;
}

// splits a line into the opcode and operands
u_byte split_ops(char *line, char **array) {
  u_byte count = 0;
  char *token = line;

  // copies a pointer to the line into string to prevent memory leaks through strsep
  char *string = line;
  while (string != NULL) {

    // if the string has no break delimiters
    if (split_break(&string, token, START_BREAK_DELIMITER, END_BREAK_DELIMITER) && split_break(&string, token, START_CURLY_DELIMITER, END_CURLY_DELIMITER)) {

      // splits the string at a ',' (OPERAND_DELIMITER), copying the left side into token and keeping the right side in string
      token = strsep(&string, OPERAND_DELIMITER);

      // checks a token is valid
      if (token == NULL) break;
      if (!strcmp(token, "")) continue;

      // handles the shift type by allowing a space between the shift type and shift value
      if (!strcmp(token, "lsl") || !strcmp(token, "lsr") || !strcmp(token, "asr") || !strcmp(token, "ror")) {
        char *shift_val = strsep(&string, OPERAND_DELIMITER);
        char *shift_type = malloc((strlen(token) + 1)* sizeof(char));
        strcpy(shift_type, token);
        sprintf(token, "%s %s", shift_type, shift_val);
        free(shift_type);
      }
    }

    // removes line endings from the token
    token[strcspn(token, "\r\n")] = 0;
    // mallocs space for the string in the array of pointers
    array[count] = malloc((strlen(token) + 1)* sizeof(char));
    // copies the token into the array
    strcpy(array[count++], token);
  }
  return count;
}

// populates an instruction with data from a file line (now just a string containing an instruction)
void populate_instruction(instruction_t *instruction, char *line) {

  // splits at a ' ' (OPCODE_DELIMITER) to find the opcode
  char *token;
  token = strsep(&line, OPCODE_DELIMITER);
  if (token == NULL) return;
  instruction -> opcode = get_opcode(token);

  // calls split_ops to split into the operands and saves the no of ops into a variable
  instruction -> no_of_ops = split_ops(line, instruction -> ops);

}

void tokenize(assembler *assembler, bool has_label) {

    // base case: when there are no lines left to tokenize
    if (assembler -> line_pointer >= assembler -> no_lines) return;

    // gets the line (string) from assembler and skips if line is blank
    char *line = assembler -> lines[assembler -> line_pointer++];
    if (!strcmp(line, "")) {
      tokenize(assembler, has_label);
      return;
    };
    instruction_t *instruction;

    // creates a new instruction and tokenize's the line
    if (!has_label) {

      // mallocs space for the instruction
      instruction = malloc(sizeof(instruction_t));
      *instruction = INIT_INSTRUCTION;

      // checks if the line contains a ':' (LABEL_DELIMITER) and hence if the line is a label
      char *str = strchr(line, LABEL_DELIMITER);
      instruction -> has_label = str != NULL;

      // if the line is a label, save the label to the instruction and call
      // tokenize again to populate this instruction with data from next line
      if (instruction -> has_label) {
        int colon = str - line;
        instruction -> label = malloc(sizeof(char) * (colon + 1));
        for (int i = 0; i < colon; i++) {
          instruction -> label[i] = line[i];
        }
        instruction -> label[colon] = '\0';

        u_address label_address = (assembler -> instructions -> used) * 4;
        st_insert(assembler -> table, instruction -> label, label_address);

        // else populate instruction with data from this line
      } else {
        populate_instruction(instruction, line);
      }

      // adds the instruction to the dynamic instructions array and recursively calls tokenize
      instruction_array_add(assembler -> instructions, instruction);
      tokenize(assembler, instruction -> has_label);

    } else {
      // populates the previously created instruction with data from this line
      instruction = assembler -> instructions -> array[assembler -> instructions -> used - 1];
      populate_instruction(instruction, line);
      tokenize(assembler, false);

    }
}
