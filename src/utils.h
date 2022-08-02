#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "definitions.h"

#define BYTE_2_SHIFT_VAL 8
#define BYTE_3_SHIFT_VAL 16
#define BYTE_4_SHIFT_VAL 24

void errorAndExit(char errorMessage[]);
u_word to_little_endian(u_word val);

#endif
