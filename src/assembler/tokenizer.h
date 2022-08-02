#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../definitions.h"
#include "definitions.h"
#include "../utils.h"

#define NO_OPCODES 47

extern const char *opcodes[NO_OPCODES];

#define MAX_ARGS 6

#define LABEL_DELIMITER       ':'
#define OPERAND_DELIMITER     ", "
#define OPCODE_DELIMITER      " "
#define START_BREAK_DELIMITER '['
#define END_BREAK_DELIMITER   "]"
#define START_CURLY_DELIMITER '{'
#define END_CURLY_DELIMITER   "}"

u_byte split_ops(char *line, char **array);
void tokenize(assembler *assembler, bool has_label);

#endif
