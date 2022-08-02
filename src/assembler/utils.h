#ifndef ASSEMBLE_UTILS_H
#define ASSEMBLE_UTILS_H

#include "../definitions.h"
#include "definitions.h"

#define BYTE_2_SHIFT_VAL 8
#define BYTE_3_SHIFT_VAL 16
#define BYTE_4_SHIFT_VAL 24

u_word regToInt(char *registers);
u_word toInt(char *integer);
void set_bits(int n, u_word val, u_word *result);
int count_commas(char *line);

#endif
