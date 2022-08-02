#ifndef ASSEMBLER_IO_H
#define ASSEMBLER_IO_H

#include <stdio.h>
#include <stdlib.h>

#include "../utils.h"
#include "definitions.h"

#define MAX_CHARS 511

void readInstr(assembler *assembler, char* path);
void writeInstr(assembler *ass, char* path);

#endif
