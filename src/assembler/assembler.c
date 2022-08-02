#include "definitions.h"
#include "io.h"
#include "../utils.h"
#include "tokenizer.h"
#include "single_data_transfer.h"
#include "multiply.h"
#include "branch.h"
#include "data_processing.h"
#include "../extension/assembler/block_data_transfer.h"
#include "../extension/assembler/single_data_swap.h"

static const assembler INIT_ASS = {
  .line_pointer = 0,
  .no_lines = 0,
  .lines = NULL,
  .instruction_pointer = 0,
  .instructions = NULL,
  .values = NULL,
  .output = NULL,
  .table = NULL
};

void free_instructions(assembler *ass) {
  for (int i = 0; i < ass -> instructions -> used; i++) {
    instruction_t *instruction = ass -> instructions -> array[i];
    if (instruction -> has_label) free(instruction -> label);
    for (int j = 0; j < instruction -> no_of_ops; j++) {
      free(instruction -> ops[j]);
    }
    free(instruction);
  }
}

void free_assembler(assembler *ass) {

  st_free(ass -> table);

  free_instructions(ass);
  instruction_array_free(ass -> instructions);
  free(ass -> instructions);

  word_array_free(ass -> values);
  free(ass -> values);

  word_array_free(ass -> output);
  free(ass -> output);

  for (int i = 0; i < ass -> no_lines; i++) free(ass -> lines[i]);
  free(ass -> lines);

}

void process_instruction(assembler *ass) {

  if (ass -> instruction_pointer >= ass -> instructions -> used) return;

  instruction_t *instruction = ass -> instructions -> array[ass -> instruction_pointer];
  opcode_t opcode = instruction -> opcode;
  u_word out;
  if (opcode < MUL) {
    out = data_processing(instruction);
  } else if (opcode < LDR) {
    out = multiply(instruction);
  } else if (opcode < BEQ) {
    out = single_data_transfer(ass);
  } else if (opcode < LSL) {
    out = branch(ass);
  } else if (opcode == LSL){
    out = process_lsl(instruction);
  } else if (opcode == ANDEQ) {
    out = 0;
  } else if (opcode < POP) {
    out = blockDataTransfer(instruction);
  } else if (opcode == POP) {
    out = process_pop(instruction);
  } else if (opcode == PUSH) {
    out = process_push(instruction);
  } else if (opcode < NONE) {
    out = single_data_swap(instruction);
  } else if (opcode == NONE) {
    process_instruction(ass);
    return;
  }

  word_array_add(ass -> output, out);
  ass -> instruction_pointer++;
  process_instruction(ass);
}

int main(int argc, char const *argv[]) {

  if (argc != 3 && argc != 4) {
    errorAndExit("Invalid arguments.");
  }

  bool debug = false;
  if (argc == 4) {
    debug = !strcmp(argv[3], "-debug");
  }

  assembler *ass = malloc(sizeof(assembler));
  if (ass == NULL) {
    errorAndExit("Unable to allocate memory for assembler.");
  }

  *ass = INIT_ASS;
  ass -> table = create_table();

  ass -> instructions = malloc(sizeof(instruction_array_t));
  if (ass -> instructions == NULL) errorAndExit("Unable to allocate memory for instructions.");

  ass -> output = malloc(sizeof(word_array_t));
  if (ass -> output == NULL) errorAndExit("Unable to allocate memory for output.");

  ass -> values = malloc(sizeof(word_array_t));
  if (ass -> values == NULL) errorAndExit("Unable to allocate memory for values.");

  instruction_array_init(ass -> instructions);
  word_array_init(ass -> values);
  word_array_init(ass -> output);
  readInstr(ass, argv[1]);

  tokenize(ass, false);
  process_instruction(ass);

  if (!debug) {
    writeInstr(ass, argv[2]);
  }

  free_assembler(ass);
  free(ass);

  return EXIT_SUCCESS;
}
