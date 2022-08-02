#ifndef ASSEMBLE_DEFINITONS_H
#define ASSEMBLE_DEFINITONS_H

#include <string.h>

#include "../definitions.h"
#include "symbol_table.h"

#define MAX_OPS             4
#define DEFAULT_ARRAY_SIZE  1
#define COND_SHIFT_VAL      28
#define MAX_FOR_MOV       0xFF

#define IMMEDIATE_CHAR      '#'
#define SUBTRACT_CHAR       '-'
#define COMMA_CHAR          ','
#define END_CHAR            '\0'

struct instruction_array_t;
struct word_array_t;

typedef enum {
  ADD, //DATA PROCESSING
  SUB,
  RSB,
  AND,
  EOR,
  MOV,
  TST,
  TEQ,
  CMP,
  ORR,
  MUL, //MULTIPLY - 10
  MLA,
  LDR, //SDT - 12
  STR,
  BEQ, //BRANCH - 14
  BNE,
  BGE,
  BLT,
  BGT,
  BLE,
  B,
  LSL, //SPECIAL - 21
  ANDEQ,
  LDMED, //BDT - 23
  LDMFD, // unused
  LDMEA, // unused
  LDMFA, // unused
  STMFA, // unused
  STMEA, // unused
  STMFD, // unused
  STMED,
  POP,
  PUSH,
  SWP, // SWP - 33
  SWPEQ,
  SWPNE,
  SWPGE,
  SWPLT,
  SWPGT,
  SWPLE,
  SWPB,
  SWPEQB,
  SWPNEB,
  SWPGEB,
  SWPLTB,
  SWPGTB,
  SWPLEB,
  NONE //NONE - 47
} opcode_t;

typedef struct {
  char *label;
  opcode_t opcode;
  char *ops[MAX_OPS];
  u_byte no_of_ops;
  bool has_label;
} instruction_t;

typedef struct {
  u_word line_pointer;
  char **lines;
  u_word no_lines;
  size_t instruction_pointer;
  struct instruction_array_t *instructions;
  struct word_array_t *values;
  struct word_array_t *output;
  symbolTable *table;
} assembler;

typedef struct word_array_t {
  u_word *array;
  size_t size;
  size_t used;
} word_array_t;

void word_array_init(word_array_t *array);
void word_array_add(word_array_t *a, u_word val);
void word_array_free(word_array_t *a);
u_word word_array_pop_last(word_array_t *a);

typedef struct instruction_array_t {
  instruction_t **array;
  size_t size;
  size_t used;
} instruction_array_t;

void instruction_array_init(instruction_array_t *array);
void instruction_array_add(instruction_array_t *a, instruction_t *val);
void instruction_array_free(instruction_array_t *a);

#endif
